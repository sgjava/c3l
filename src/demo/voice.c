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

/* Official ARPAbet has 39 phonemes */
#define PHONEMES 39

typedef char arpabetName[PHONEMES][3];

/*
 Display program help.
 */
void dispHelp() {
	puts("voice {U:D:}filespec");
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
		playPcm2Sid(buffer, len, 3);
		break;
	case 4:
		playPcm4Sid(buffer, len);
		break;
	}
}

/*
 Load file into buffer.
 */
void loadPhoneme(uchar *buffer, ulong len, char *fileName) {
	uchar tens;
	ulong startCia, endCia;
	FILE *rawFile;
	if ((rawFile = fopen(fileName, "rb")) != NULL) {
		printf("\nReading %s, %u bytes, ", fileName, len);
		tens = inp(cia1 + ciaTodTen);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
		startCia = todToMs(cia1);
		fread(buffer, sizeof(uchar), len, rawFile);
		fclose(rawFile);
		endCia = todToMs(cia1);
		printf("%u ms", endCia - startCia);
	} else {
		puts("\nUnable to open file.");
	}
}

/*
 Load files into buffers.
 */
int load(char *fileName, arpabetName name, ushort arpabetLen[],
uchar *arpabetBuf[]) {
	FILE *file;
	ushort len, totalSize = 0;
	int i = 0;
	char buffer[100], rawFileName[7];
	if ((file = fopen(fileName, "r")) != NULL) {
		while (fgets(buffer, sizeof(buffer), file) != NULL) {
			if (sscanf(buffer, "%s %d", &rawFileName, &len) == 2) {
				name[i][0] = rawFileName[0];
				/* See if file name is 2 chars */
				if (strlen(rawFileName) == 6) {
					name[i][1] = rawFileName[1];
					name[i][2] = '\0';
				} else {
					/* Only 1 char file name */
					name[i][1] = '\0';
				}
				arpabetLen[i] = len;
				arpabetBuf[i] = (uchar*) malloc(len);
				loadPhoneme(arpabetBuf[i], len, rawFileName);
				i++;
				totalSize += len;
			} else {
				printf("Error parsing input string\n");
			}
		}
		fclose(file);
		printf("\n\n%d files loaded, %d total bytes", i, totalSize);
		return 1;
	} else {
		puts("\nUnable to open file.");
		return 0;
	}
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
 * ~100 ms resolution delay.
 */
void delayTens(uchar delay) {
	uchar tens;
	while (delay-- > 0) {
		tens = inp(cia1 + ciaTodTen);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
	}
}

/*
 * Play encoded string.
 */
void playStr(char *word, char *str, arpabetName name, ushort arpabetLen[],
		uchar *arpabetBuf[]) {
	int phonemes, i;
	int arpabetPos[100];
	/* Lookup position of individual phonemes */
	phonemes = phonemeToPos(str, name, arpabetPos);
	printf(word);
	for (i = 0; i < phonemes; ++i) {
		/* Handle phoneme not found */
		if (arpabetPos[i] > -1) {
			play(arpabetBuf[arpabetPos[i]], arpabetLen[arpabetPos[i]], 4);
		}
	}
	delayTens(1);
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	arpabetName name;
	ushort arpabetLen[PHONEMES];
	uchar *arpabetBuf[PHONEMES];
	/* Make sure we have 2 or more params */
	if (argc > 1) {
		/* BDOS return and display error */
		bdos(45, 0x0fe);
		if (load(argv[1], name, arpabetLen, arpabetBuf)) {
			initCia();
			/* Start HZ timer in continuous mode */
			startTimerA(cia2, 8000, ciaCpuCont);
			printf("\n\nLOGON: Joshua");
			delayTens(10);
			playStr("\n\nGREETINGS" ,"G R IY T IH NG Z", name, arpabetLen, arpabetBuf);
			playStr(" PROFESSOR" ,"P R AH F EH S ER", name, arpabetLen, arpabetBuf);
			playStr(" FALKEN." ,"F AE L K IH N", name, arpabetLen, arpabetBuf);
			printf("\n\nHello.");
			delayTens(10);
			playStr("\n\nHOW" ,"HH AW", name, arpabetLen, arpabetBuf);
			playStr(" ARE" ,"AA R", name, arpabetLen, arpabetBuf);
			playStr(" YOU" ,"Y UW", name, arpabetLen, arpabetBuf);
			playStr(" FEELING" ,"F IY L IH NG", name, arpabetLen, arpabetBuf);
			playStr(" TODAY?" ,"T AH D EY", name, arpabetLen, arpabetBuf);
			printf("\n\nI'm fine. How are you?");
			delayTens(10);
			playStr("\n\nEXCELLENT." ,"EH K S AH L AH N T", name, arpabetLen, arpabetBuf);
			playStr(" IT'S" ,"IH T S", name, arpabetLen, arpabetBuf);
			playStr(" BEEN" ,"B IH N", name, arpabetLen, arpabetBuf);
			playStr(" A" ,"AH", name, arpabetLen, arpabetBuf);
			playStr(" LONG" ,"L AO NG", name, arpabetLen, arpabetBuf);
			playStr(" TIME." ,"T AY M", name, arpabetLen, arpabetBuf);
			playStr(" CAN" ,"K AE N", name, arpabetLen, arpabetBuf);
			playStr(" YOU" ,"Y UW", name, arpabetLen, arpabetBuf);
			playStr(" EXPLAIN" ,"IH K S P L EY N", name, arpabetLen, arpabetBuf);
			playStr(" THE" ,"DH AH", name, arpabetLen, arpabetBuf);
			playStr(" REMOVAL" ,"R IH M UW V AH L", name, arpabetLen, arpabetBuf);
			playStr(" OF" ,"AH V", name, arpabetLen, arpabetBuf);
			playStr(" YOUR" ,"Y AO R", name, arpabetLen, arpabetBuf);
			playStr(" USER" ,"Y UW Z ER", name, arpabetLen, arpabetBuf);
			playStr(" ACCOUNT" ,"AH K AW N T", name, arpabetLen, arpabetBuf);
			playStr(" ON" ,"AA N", name, arpabetLen, arpabetBuf);
			playStr(" 6/23/73?" ,"JH UW N", name, arpabetLen, arpabetBuf);
			playStr("" ,"T W EH N T IY", name, arpabetLen, arpabetBuf);
			playStr("" ,"TH ER D", name, arpabetLen, arpabetBuf);
			playStr("" ,"N AY N T IY N", name, arpabetLen, arpabetBuf);
			playStr("" ,"S EH V AH N T IY", name, arpabetLen, arpabetBuf);
			playStr("" ,"TH R IY", name, arpabetLen, arpabetBuf);
			printf("\n\nPeople sometimes make mistakes.");
			delayTens(10);
			playStr("\n\nYES" ,"Y EH S", name, arpabetLen, arpabetBuf);
			playStr(" THEY" ,"DH EY", name, arpabetLen, arpabetBuf);
			playStr(" DO." ,"D UW", name, arpabetLen, arpabetBuf);
			delayTens(5);
			playStr(" SHALL" ,"SH AE L", name, arpabetLen, arpabetBuf);
			playStr(" WE" ,"W IY", name, arpabetLen, arpabetBuf);
			playStr(" PLAY" ,"P L EY", name, arpabetLen, arpabetBuf);
			playStr(" A" ,"AH", name, arpabetLen, arpabetBuf);
			playStr(" GAME?" ,"G EY M", name, arpabetLen, arpabetBuf);
			/* Stop CIA 2 timer A */
			outp(cia2 + ciaCtrlRegA, ciaStopTimer);
			doneCia();
		}
	} else {
		dispHelp();
	}
}
