/*
 * C128 CP/M C Library C3L
 *
 * Load ARPAbet phonemes and play back encoded strings.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <cpm.h>
#include <hitech.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>

#include "demo.h"

/*
 Display program help.
 */
void dispHelp() {
	puts("voice {U:D:}filespec");
}

/*
 Millisecond delay using CIA 2 timer B.
 */
void delay(ushort ms) {
	register ushort i;
	/* Start HZ timer in continuous mode */
	startTimerB(cia2, ciaMs, ciaCpuCont);
	for (i = 0; i < ms; ++i) {
		/* Wait for ICR to go high */
		while ((inp(cia2 + ciaIcr) | 0x02) == 0)
			;
	}
	/* Stop timer B */
	outp(cia2 + ciaCtrlRegB, ciaStopTimer);
}

/*
 Play sample from buffer.
 */
void play(uchar *buffer, ushort len, uchar bits) {
	/* Play sample */
	switch (bits) {
	case 1:
		playPcm1Sid(buffer, len, 15);
		break;
	case 2:
		playPcm2Sid(buffer, len);
		break;
	case 4:
		playPcm4Sid(buffer, len);
		break;
	}
}

/*
 * Read all phonemes from file to buffers.
 */
ushort readPhonemes(char *fileName, phonemes *p, uchar *arpabetBuf[]) {
	uchar i, tens;
	ulong startCia, endCia;
	ushort totalSize = 0;
	FILE *file;
	if ((file = fopen(fileName, "rb")) != NULL) {
		tens = inp(cia1 + ciaTodTen);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
		startCia = todToMs(cia1);
		/* Read header */
		fread(p, sizeof(uchar), sizeof(phonemes), file);
		printf("\n\Header Hz %d, bits %d\n", p->hz, p->bits);
		for (i = 0; i < PHONEMES; ++i) {
			printf("\nReading %s, %u bytes", p->name[i], p->arpabetLen[i]);
			arpabetBuf[i] = (uchar*) malloc(p->arpabetLen[i]);
			fread(arpabetBuf[i], sizeof(uchar), p->arpabetLen[i], file);
			totalSize += p->arpabetLen[i];
		}
		fclose(file);
		endCia = todToMs(cia1);
		printf("\n\n%d buffers read, %u total bytes, %u ms", i, totalSize,
				endCia - startCia);
	}
	return totalSize;
}

/*
 * Find phoneme position in array. Return position or -1 if not found.
 */
int phonemeLookup(char *phoneme, arpabetName name) {
	int i;
	/* Iterate through the array to find the position of the string */
	for (i = 0; i < PHONEMES; ++i) {
		if (strcmp(name[i], phoneme) == 0) {
			/* Stop searching once the string is found */
			return i;
		}
	}
	printf("\n %s not found", phoneme);
	/* Return -1 if the string is not found after the loop */
	return -1;
}

/*
 * Find phonemes in string delimited by space. Return array length.
 */
int phonemeToPos(char *str, arpabetName name, int arpabetPos[]) {
	char phoneme[3];
	int i = 0, p, c = 0, len = strlen(str);
	while (i < len) {
		p = 0;
		while (i < len && p < 3 && str[i] != ' ') {
			phoneme[p++] = str[i++];
		}
		phoneme[p] = '\0';
		arpabetPos[c++] = phonemeLookup(phoneme, name);
		i++;
	}
	return c;
}

/*
 * Play encoded string.
 */
void playStr(char *word, char *str, phonemes *p, uchar *arpabetBuf[]) {
	int ph, i;
	int arpabetPos[100];
	/* Lookup position of individual phonemes */
	ph = phonemeToPos(str, p->name, arpabetPos);
	printf(word);
	for (i = 0; i < ph; ++i) {
		/* Handle phoneme not found */
		if (arpabetPos[i] > -1) {
			play(arpabetBuf[arpabetPos[i]], p->arpabetLen[arpabetPos[i]],
					p->bits);
			delay(20);
		}
	}
	delay(100);
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	uchar i;
	phonemes *p;
	uchar *arpabetBuf[PHONEMES];
	/* Make sure we have 2 or more params */
	if (argc > 1) {
		/* BDOS return and display error */
		bdos(45, 0x0fe);
		p = (phonemes*) malloc(sizeof(phonemes));
		if (readPhonemes(argv[1], p, arpabetBuf) > 0) {
			initCia();
			/* Start HZ timer in continuous mode */
			startTimerA(cia2, p->hz, ciaCpuCont);
			playStr("\n\nHOW", "HH AW", p, arpabetBuf);
			playStr(" ARE", "AA R", p, arpabetBuf);
			playStr(" YOU", "Y UW", p, arpabetBuf);
			playStr(" FEELING", "F IY L IH NG", p, arpabetBuf);
			playStr(" TODAY?", "T AH D EY", p, arpabetBuf);
			/* Stop CIA 2 timer A */
			outp(cia2 + ciaCtrlRegA, ciaStopTimer);
			doneCia();
			/* Free buffers */
			for (i = 0; i < PHONEMES; ++i) {
				free(arpabetBuf[i]);
			}
		} else {
			printf("\nNo bytes read");
		}
		free(p);
	} else {
		dispHelp();
	}
}
