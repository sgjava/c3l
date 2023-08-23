/*
 * C128 CP/M C Library C3L
 *
 * Convert 8 bit PCM to 4 bit PCM.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <cpm.h>
#include <hitech.h>
#include <stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>

#include "demo.h"

/*
 Size of conversion buffer (make divisible by 8).
 */
#define BUF_SIZE 8192

/*
 Display program help.
 */
void dispHelp() {
	puts("\nconvpcm {U:D:}filespec {U:D:}filespec bits");
	puts(
			"convpcm FILENAME.SND FILENAME.RAW 4 (.SND is 8 bit and .RAW is 4 bit)");
}

/*
 Display current time in SS.S format using CIA 2's TOD clock.
 */
void dispTime() {
	printf(", %d mins, %d.%d secs\n", bcdToByte(inp(cia2TodMin)),
			bcdToByte(inp(cia2TodSec)), bcdToByte(inp(cia2TodTen)));
}

/*
 Convert 8 bit raw data to 4 bit raw data.
 */
ushort convert8to4(uchar *buffer, ushort bufSize) {
	ushort i;
	for (i = 0; i < bufSize; i += 2) {
		buffer[i >> 1] = (buffer[i] & 0xf0) | (buffer[i + 1] >> 4);
	}
	/* Two 4 bit samples in a byte */
	return bufSize / 2;
}

/*
 Convert 8 bit raw data to 1 bit raw data.
 */
ushort convert8to1(uchar *buffer, ushort bufSize) {
	static uchar bitTable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
	uchar sample;
	ushort i, b;
	for (i = 0; i < bufSize; i += 8) {
		sample = 0x00;
		/* Pack 8 bytes into 1 byte */
		for (b = 0; b < 8; ++b) {
			if (buffer[i + b] > 0x7f) {
				sample = sample | (bitTable[b]);
			}
		}
		buffer[i >> 3] = sample;
	}
	/* Eight 1 bit samples in a byte */
	return bufSize / 8;
}

/*
 Convert 8 bit raw data to 4, 2 or 1 bit raw data.
 */
void convert(char *inFileName, char *outFileName, uchar *buffer, ushort bufSize,
uchar bits) {
	FILE *inFile, *outFile;
	struct stat statRec;
	ushort bytesRead, bytesWrite;
	ulong cnvBytes, cnvStep, cnvNext;
	printf("\n");
	/* Check bits valid value */
	if (bits == 4 || bits == 2 || bits == 1) {
		if (stat(inFileName, &statRec) == 0) {
			if ((inFile = fopen(inFileName, "rb")) != NULL) {
				if ((outFile = fopen(outFileName, "wb")) != NULL) {
					cnvBytes = 0;
					/* Progress steps */
					cnvStep = statRec.st_size / 10;
					cnvNext = cnvStep;
					printf(
							"Converting %s, %ld bytes, ..........\b\b\b\b\b\b\b\b\b\b",
							inFileName, statRec.st_size);
					setCiaTod(0, 0, 0, 0);
					do {
						bytesRead = fread(buffer, sizeof(uchar), bufSize,
								inFile);
						/* Convert 8 bit to 4, 2 or 1 */
						switch (bits) {
						case 1:
							bytesWrite = convert8to1(buffer, bytesRead);
							break;
						case 4:
							bytesWrite = convert8to4(buffer, bytesRead);
							break;
						}
						fwrite(buffer, sizeof(uchar), bytesWrite, outFile);
						cnvBytes += bytesRead;
						while (cnvBytes >= cnvNext) {
							printf("*"); /* show progress */
							cnvNext += cnvStep;
						}
					} while (bytesRead == bufSize);
					fclose(outFile);
					dispTime();
				} else {
					puts("\nUnable to open output file.");
				}
				fclose(inFile);
			} else {
				puts("\nUnable to open input file.");
			}
		} else {
			puts("\nUnable to open input file.");
		}
	} else {
		puts("\nBits value must 4, 2 or 1.");
	}
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	uchar *buffer, bits;
	/* Make sure we have 4 or more params */
	if (argc == 4) {
		/* Alloc conversion buffer */
		buffer = (uchar*) malloc(BUF_SIZE);
		if (buffer != NULL) {
			/* BDOS return and display error mode */
			bdos(45, 0x0FE);
			/* Convert bits param to unsigned char */
			sscanf(argv[3], "%d", &bits);
			/* Convert raw file */
			convert(argv[1], argv[2], buffer, BUF_SIZE, bits);
			/* Dispose buffer */
			free(buffer);
		}
	} else
		dispHelp();
}
