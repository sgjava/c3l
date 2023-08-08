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

/*
 Size of conversion buffer
 */
#define BUF_SIZE 8192

/*
 Display program help.
 */
void dispHelp() {
	puts("\nconvpcm {U:D:}filespec {U:D:}filespec");
	puts("convpcm FILENAME.SND FILENAME.RAW (.SND is 8 bit and .RAW is 4 bit)");
}

/*
 Set CIA 2 TOD clock.
 */
void setCiaTod(uchar hour, uchar min, uchar sec, uchar tenth) {
	/* Bit 7 = 0 sets TOD clock */
	outp(cia2CtrlRegB, inp(cia2CtrlRegB) & 0x7f);
	/* CIA 2 TOD hour */
	outp(cia2TodHrs, hour);
	/* CIA 2 TOD minute */
	outp(cia2TodMin, min);
	/* CIA 2 TOD second */
	outp(cia2TodSec, sec);
	/* CIA 2 TOD tenth second */
	outp(cia2TodTen, tenth);
}

/*
 * Convert bcd byte to base 10 byte.
 */
uchar bcdToByte(uchar bcd) {
	return ((bcd >> 4) * 10) + (bcd & 0x0f);
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
void convert(char *inFileName, char *outFileName, uchar *buffer, ushort bufSize) {
	FILE *inFile, *outFile;
	struct stat statRec;
	ushort i, bytesRead;
	ulong cnvBytes, cnvStep, cnvNext;
	printf("\n");
	if (stat(inFileName, &statRec) == 0) {
		if ((inFile = fopen(inFileName, "rb")) != NULL) {
			if ((outFile = fopen(outFileName, "wb")) != NULL) {
				cnvBytes = 0;
				/* Progress steps */
				cnvStep = statRec.st_size / 10;
				cnvNext = cnvStep;
				printf(
						"\nConverting %s, %ld bytes, ..........\b\b\b\b\b\b\b\b\b\b",
						inFileName, statRec.st_size);
				setCiaTod(0, 0, 0, 0);
				do {
					bytesRead = fread(buffer, sizeof(uchar), bufSize, inFile);
					/* Pack 2 8 bit samples into 1 byte */
					for (i = 0; i < bytesRead; i += 2) {
						buffer[i >> 1] = (buffer[i] & 0xf0)
								| (buffer[i + 1] >> 4);
					}
					fwrite(buffer, sizeof(uchar), bytesRead >> 1, outFile);
					cnvBytes += bytesRead;
					while (cnvBytes >= cnvNext) {
						printf("*"); /* show progress */
						cnvNext += cnvStep;
					}
				} while (bytesRead == bufSize);
				fclose(outFile);
				dispTime();
			} else
				puts("\nUnable to open output file.");
			fclose(inFile);
		} else
			puts("\nUnable to open input file.");
	} else
		puts("\nUnable to open input file.");
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	uchar *buffer;
	/* Make sure we have 3 or more params */
	if (argc == 3) {
		/* Alloc conversion buffer */
		buffer = (uchar*) malloc(BUF_SIZE);
		if (buffer != NULL) {
			/* BDOS return and display error mode */
			bdos(45, 0x0FE);
			/* Convert raw file */
			convert(argv[1], argv[2], buffer, BUF_SIZE);
			/* Dispose buffer */
			free(buffer);
		}
	} else
		dispHelp();
}
