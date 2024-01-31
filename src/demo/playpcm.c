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
	puts("\nplaypcm {U:D:}filespec hertz bits {sn}");
	puts("playpcm filename.raw 8000 4 sn (swap nibbles before playing)");
	puts("playpcm filename.raw 16000 1 (no nibble swap)");
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
	uchar tens;
	ulong startCia, endCia;
	ushort i;
	printf("Swapping nibbles, ");
	tens = inp(cia1 + ciaTodTen);
	/* Wait for tenth of a second to change */
	while (inp(cia1 + ciaTodTen) == tens)
		;
	startCia = todToMs(cia1);
	for (i = 0; i < len; i++) {
		buffer[i] = (buffer[i] << 4) | (buffer[i] >> 4);
	}
	endCia = todToMs(cia1);
	printf("%u ms\n", endCia - startCia);
}

/*
 Play sample from buffer.
 */
void play(uchar *buffer, ushort len, ushort hz, uchar bits) {
	uchar tens;
	ulong startCia, endCia;
	/* Start HZ timer in continuous mode */
	startTimerA(cia2, hz, ciaCpuCont);
	printf("Playing, ");
	tens = inp(cia1 + ciaTodTen);
	/* Wait for tenth of a second to change */
	while (inp(cia1 + ciaTodTen) == tens)
		;
	startCia = todToMs(cia1);
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
	endCia = todToMs(cia1);
	/* Stop CIA 2 timer A */
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	printf("%u ms\n", endCia - startCia);
}

/*
 Load file into buffer.
 */
void loadAll(uchar *buffer, ulong len, char *fileName) {
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
		printf("%u ms\n", endCia - startCia);
	} else
		puts("\nUnable to open file.");
}

/*
 * Main function.
 */
main(int argc, char *argv[]) {
	uchar *buffer, bits;
	ushort minHz = 4001, maxHz = 19001, maxFileSize = 45056, hz;
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
						loadAll(buffer, fileSize, argv[1]);
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
					free(buffer);
				} else if (fileSize > 0) {
					puts("\nFile too large.");
				} else {
					puts("\nUnable to open file.");
				}
			} else {
				puts("\nBits value must 4, 2 or 1.");
			}
		} else {
			puts("\nHz value must be >= 4000 and <= 19000.");
		}
	} else {
		dispHelp();
	}
}
