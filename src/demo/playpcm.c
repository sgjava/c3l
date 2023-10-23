/*
 * C128 CP/M C Library C3L
 *
 * Play 4, 2 and 1 bit PCM files with nibble swapping feature.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <cpm.h>
#include <hitech.h>
#include <stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>

#include "demo.h"

/*
 Display program help.
 */
void dispHelp() {
	puts("\nplaypcm4 {U:D:}filespec hertz bits {sn}");
	puts("playpcm4 filename.raw 8000 4 sn (swap nibbles before playing)");
	puts("playpcm4 filename.raw 15000 1 (no nibble swap)");
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
	/* Reading TOD clock hours stops updating time */
	inp(cia2+ciaTodHrs);
	printf("%d.%d secs\n", bcdToByte(inp(cia2+ciaTodSec) & 0x7f),
			bcdToByte(inp(cia2+ciaTodTen) & 0x0f));
}

/*
 Return file size or 0 for error.
 */
ulong getFileSize(char *fileName) {
	struct stat statRec;
	if (stat(fileName, &statRec) == 0) {
		return statRec.st_size;
	} else {
		return 0;
	}
}

/*
 Swap nibbles in buffer for inverted RAWs.
 */
void swapNibbles(uchar *buffer, ushort len) {
	ushort i;
	printf("Swapping nibbles, ");
	setCiaTod(cia2, 0, 0, 0, 0);
	for (i = 0; i < len; i++) {
		buffer[i] = (buffer[i] << 4) | (buffer[i] >> 4);
	}
	dispTime();
}

/*
 Play sample from buffer.
 */
void play(uchar *buffer, ushort len, ushort hz, uchar bits) {
	/* Start HZ timer */
	startTimer(cia2, hz);
	printf("Playing, ");
	setCiaTod(cia2, 0, 0, 0, 0);
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
	dispTime();
	/* Stop CIA 2 timer A */
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
}

/*
 Load file into buffer.
 */
void load(uchar *buffer, ulong len, char *fileName) {
	FILE *rawFile;
	if ((rawFile = fopen(fileName, "rb")) != NULL) {
		printf("\nReading %s, %u bytes, ", fileName, len);
		setCiaTod(cia2, 0, 0, 0, 0);
		fread(buffer, sizeof(uchar), len, rawFile);
		fclose(rawFile);
		dispTime();
	} else
		puts("\nUnable to open file.");
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	uchar *buffer, bits;
	ushort minHz = 3999, maxHz = 15001, maxFileSize = 45056, hz;
	ulong fileSize;
	/* Make sure we have 4 or more params */
	if (argc > 3) {
		/* Convert hz param to unsigned short */
		sscanf(argv[2], "%d", &hz);
		/* Convert bits param to unsigned char */
		sscanf(argv[3], "%d", &bits);
		/* Check hz range */
		if (hz > minHz && hz < maxHz) {
			/* Check bits valid value */
			if (bits == 4 || bits == 2 || bits == 1) {
				/* BDOS return and display error */
				bdos(45, 0x0fe);
				/* Get raw file size */
				fileSize = getFileSize(argv[1]);
				/* Check file size */
				if (fileSize > 0 && fileSize < maxFileSize) {
					/* Allocate buffer */
					buffer = (uchar*) malloc(fileSize);
					if (buffer != NULL) {
						load(buffer, fileSize, argv[1]);
						/* Swap nibbles if requested */
						if (strcmp(argv[4], "SN") == 0 && bits == 4) {
							swapNibbles(buffer, fileSize);
						}
						initCia();
						play(buffer, fileSize, hz, bits);
						free(buffer);
						doneCia();
					} else {
						puts("\nUnable to allocate memory.");
					}
				} else if (fileSize > 0) {
					puts("\nFile too large.");
				} else {
					puts("\nUnable to open file.");
				}
			} else {
				puts("\nBits value must 4, 2 or 1.");
			}
		} else {
			puts("\nHz value must be >= 4000 and <= 15000.");
		}
	} else {
		dispHelp();
	}
}
