/*
 * C128 CP/M C Library C3L
 *
 * Load ARPAbet phonemes and compile into single file.
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
	puts("compile {U:D:}filespec Hz bits {U:D:}filespec");
}

/*
 Load phoneme into buffer.
 */
void loadPhoneme(uchar *buffer, ulong len, char *fileName) {
	FILE *rawFile;
	if ((rawFile = fopen(fileName, "rb")) != NULL) {
		printf("\nReading %s, %u bytes", fileName, len);
		fread(buffer, sizeof(uchar), len, rawFile);
		fclose(rawFile);
	} else {
		printf("\nUnable to open file %s", fileName);
	}
}

/*
 Load all phonemes into buffers. Input file format should be FILE.RAW SIZE.
 */
ushort loadAll(char *fileName, arpabetName name, ushort arpabetLen[],
uchar *arpabetBuf[]) {
	uchar tens;
	ulong startCia, endCia;
	FILE *file;
	ushort len, totalSize = 0;
	int i = 0;
	char buffer[100], rawFileName[7];
	if ((file = fopen(fileName, "r")) != NULL) {
		tens = inp(cia1 + ciaTodTen);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
		startCia = todToMs(cia1);
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
		endCia = todToMs(cia1);
		printf("\n\n%d files loaded, %d total bytes, %u ms", i, totalSize,
				endCia - startCia);
	} else {
		puts("\nUnable to open file.");
	}
	return totalSize;
}

/*
 * Write all phonemes to a file with header describing Hz, bits, sample and length.
 */
ushort writePhonemes(char *fileName, phonemes *p, uchar *arpabetBuf[]) {
	uchar i, tens;
	ulong startCia, endCia;
	ushort totalSize = 0;
	FILE *file;
	if ((file = fopen(fileName, "wb")) != NULL) {
		tens = inp(cia1 + ciaTodTen);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
		startCia = todToMs(cia1);
		/* Write header */
		printf("\n\nWriting header Hz %d, bits %d\n", p->hz, p->bits);
		fwrite(p, sizeof(uchar), sizeof(phonemes), file);
		for (i = 0; i < PHONEMES; ++i) {
			printf("\nWriting %s, %u bytes", p->name[i], p->arpabetLen[i]);
			fwrite(arpabetBuf[i], sizeof(uchar), p->arpabetLen[i], file);
			totalSize += p->arpabetLen[i];
		}
		fclose(file);
		endCia = todToMs(cia1);
		printf("\n\n%d buffers written, %d total bytes, %u ms", i, totalSize,
				endCia - startCia);
	}
	return totalSize;
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	uchar bits, i;
	ushort hz, totalRead = 0, totalWrite = 0;
	phonemes *p;
	arpabetName name;
	ushort arpabetLen[PHONEMES];
	uchar *arpabetBuf[PHONEMES];
	/* Make sure we have 5 params */
	if (argc == 5) {
		/* Convert hz param to unsigned short */
		sscanf(argv[2], "%d", &hz);
		/* Convert bits param to unsigned char */
		sscanf(argv[3], "%d", &bits);
		/* BDOS return and display error */
		bdos(45, 0x0fe);
		totalRead = loadAll(argv[1], name, arpabetLen, arpabetBuf);
		if (totalRead) {
			p = (phonemes*) malloc(sizeof(phonemes));
			p->hz = hz;
			p->bits = bits;
			memcpy(p->arpabetLen, arpabetLen, sizeof(arpabetLen));
			memcpy(p->name, name, sizeof(name));
			totalWrite = writePhonemes(argv[4], p, arpabetBuf);
			free(p);
		}
		if (totalRead == 0 || totalRead != totalWrite) {
			printf("\n\nTotal read %u not equal to total write %u", totalRead,
					totalWrite);
		}
		/* Free buffers */
		for (i = 0; i < PHONEMES; ++i) {
			free(arpabetBuf[i]);
		}
	} else {
		dispHelp();
	}
}
