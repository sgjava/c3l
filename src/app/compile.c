/*
 * C128 CP/M C Library C3L
 *
 * Load ARPAbet phonemes and compile into single file. For z88dk is seems to run
 * main a second time. Need to find root cause, but it still works fine.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <sid.h>
#include <cpm.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024

/*
 Display program help.
 */
void dispHelp() {
	puts("compile fileinfo.txt Hz bits voice.pho\n");
}

/*
 Load phoneme into buffer.
 */
void loadPhoneme(const unsigned char *buffer, const unsigned int len, const char *fileName) {
	FILE *rawFile;
	if ((rawFile = fopen(fileName, "rb")) != NULL) {
		printf("\nReading %s, %u bytes", fileName, len);
		fread(buffer, sizeof(unsigned char), len, rawFile);
		fclose(rawFile);
	} else {
		printf("\nUnable to open file %s", fileName);
	}
}

/*
 Load all phonemes into buffers. Input file format should be FILE.RAW SIZE.
 */
unsigned int loadAll(const char *fileName, const arpabetName name,
		const unsigned int arpabetLen[], const unsigned char *arpabetBuf[]) {
	unsigned char tens;
	unsigned long startCia, endCia;
	FILE *file;
	unsigned int len, totalSize = 0;
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
				arpabetBuf[i] = (unsigned char*) malloc(len);
				loadPhoneme(arpabetBuf[i], len, rawFileName);
				i++;
				totalSize += len;
			} else {
				printf("Error parsing input string\n");
			}
		}
		fclose(file);
		endCia = todToMs(cia1);
		printf("\n\n%d files loaded, %u total bytes, %lu ms", i, totalSize,
				endCia - startCia);
	} else {
		puts("\nUnable to open file.");
	}
	return totalSize;
}

/*
 * Write all phonemes to a file with header describing Hz, bits, sample and length.
 */
unsigned int writePhonemes(const char *fileName, phonemes *p,
		const unsigned char *arpabetBuf[]) {
	unsigned char i, tens;
	unsigned long startCia, endCia;
	unsigned int totalSize = 0;
	FILE *file;
	if ((file = fopen(fileName, "wb")) != NULL) {
		tens = inp(cia1 + ciaTodTen);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
		startCia = todToMs(cia1);
		/* Write header */
		printf("\n\nWriting header Hz %d, bits %d\n", p->hz, p->bits);
		fwrite(p, sizeof(unsigned char), sizeof(phonemes), file);
		for (i = 0; i < PHONEMES; ++i) {
			printf("\nWriting %s, %u bytes", p->name[i], p->arpabetLen[i]);
			fwrite(arpabetBuf[i], sizeof(unsigned char), p->arpabetLen[i],
					file);
			totalSize += p->arpabetLen[i];
		}
		fclose(file);
		endCia = todToMs(cia1);
		printf("\n\n%d buffers written, %u total bytes, %lu ms", i, totalSize,
				endCia - startCia);
	}
	return totalSize;
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	unsigned char bits, i;
	unsigned int hz, totalRead = 0, totalWrite = 0, total, largest;
	phonemes *p;
	arpabetName name;
	unsigned int arpabetLen[PHONEMES];
	unsigned char *arpabetBuf[PHONEMES];
	mallinfo(&total, &largest);
	printf("Heap size %u largest block %u\n", total, largest);
	/* Make sure we have 5 params */
	if (argc == 5) {
		/* Convert hz param to unsigned int */
		sscanf(argv[2], "%d", &hz);
		/* Convert bits param to unsigned char */
		sscanf(argv[3], "%d", &bits);
		totalRead = loadAll(argv[1], name, arpabetLen, arpabetBuf);
		if (totalRead) {
			p = (phonemes*) malloc(sizeof(phonemes));
			p->hz = hz;
			p->bits = bits;
			memcpy(p->arpabetLen, arpabetLen, sizeof(arpabetLen));
			memcpy(p->name, name, sizeof(name));
			totalWrite = writePhonemes(argv[4], p, arpabetBuf);
			mallinfo(&total, &largest);
			printf("\nHeap size %u largest block %u\n", total, largest);
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
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
