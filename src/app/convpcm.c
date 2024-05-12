/*
 * C128 CP/M C Library C3L
 *
 * Convert 8 bit PCM to 4 bit PCM. After converting to z88dk I couldn't use the
 * heap for the buffer because it would corrupt the file name linked list.
 * Switched to local var.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#pragma output noprotectmsdos

#include <common.h>
#include <cpm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma output noprotectmsdos

/*
 Size of conversion buffer (make divisible by 2, 4 and 8).
 */
#define BUF_SIZE 1024

/*
 Display program help.
 */
void dispHelp() {
	puts("\nconvpcm input bits");
	puts("convpcm ????????.snd 4");
}

/*
 Convert 8 bit raw data to 4 bit raw data.
 */
unsigned int convert8to4(unsigned char *buffer, unsigned int bufSize) {
	unsigned int i;
	for (i = 0; i < bufSize; i += 2) {
		buffer[i >> 1] = (buffer[i] & 0xf0) | (buffer[i + 1] >> 4);
	}
	/* Two 4 bit samples in a byte */
	return bufSize / 2;
}

/*
 Convert 8 bit raw data to 2 bit raw data.
 */
unsigned int convert8to2(unsigned char *buffer, unsigned int bufSize) {
	unsigned int i, s;
	unsigned char sample;
	for (i = 0, s = 0; i < bufSize; i += 4, ++s) {
		sample = ((buffer[i] >> 6) & 0x03) | ((buffer[i + 1] >> 4) & 0x0c)
				| ((buffer[i + 2] >> 2) & 0x30) | (buffer[i + 3] & 0xc0);
		buffer[s] = sample;
	}
	/* Four 2-bit samples in a byte */
	return bufSize / 4;
}

/*
 Convert 8 bit raw data to 1 bit raw data.
 */
unsigned int convert8to1(unsigned char *buffer, unsigned int bufSize) {
	static unsigned char bitTable[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
			0x02, 0x01 };
	unsigned char sample;
	unsigned int i, b;
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
void convert(char *inFileName, char *outFileName, unsigned char bits) {
	unsigned char tens;
	FILE *inFile, *outFile;
	unsigned int bytesRead, bytesWrite;
	unsigned char buffer[BUF_SIZE];
	/* Check bits valid value */
	if (bits == 4 || bits == 2 || bits == 1) {
		if ((inFile = fopen(inFileName, "rb")) != NULL) {
			if ((outFile = fopen(outFileName, "wb")) != NULL) {
				printf("Converting %s to %s\n", inFileName, outFileName);
				do {
					bytesRead = fread(buffer, sizeof(unsigned char), BUF_SIZE,
							inFile);
					// Convert 8 bit to 4, 2 or 1
					switch (bits) {
					case 1:
						bytesWrite = convert8to1(buffer, bytesRead);
						break;
					case 2:
						bytesWrite = convert8to2(buffer, bytesRead);
						break;
					case 4:
						bytesWrite = convert8to4(buffer, bytesRead);
						break;
					}
					fwrite(buffer, sizeof(unsigned char), bytesWrite, outFile);
				} while (bytesRead == BUF_SIZE);
				fclose(outFile);
			} else {
				puts("\nUnable to open output file.");
			}
			fclose(inFile);
		} else {
			puts("\nUnable to open input file.");
		}
	} else {
		puts("\nBits value must 4, 2 or 1.");
	}
}

void changeExt(char *filename, const char *newExtension) {
	char *dot = strrchr(filename, '.'); // Find the last occurrence of '.'
	if (dot != NULL) {
		strcpy(dot + 1, newExtension); // Copy the new extension over the old one
	} else {
		strcat(filename, "."); // Add a '.' if there is no extension
		strcat(filename, newExtension); // Add the new extension
	}
}

/*
 * Process files based on standard CP/M search.
 */
processFiles(char *inFileName, unsigned char bits) {
	int curDisk, curUser, retVal, dmaOffset, i, j;
	char name[9], ext[4], dest[13];
	node *head = NULL;
	struct fcb dirFcb, retFcb;
	// FCB is 36 bytes, but only 32 are returned by CPM_FFST and CPM_FNXT calls
	unsigned char dmaBuf[144];
	curDisk = bdos(CPM_IDRV, 0);
	curUser = bdos(CPM_SUID, 0xff);
	memset(name, ' ', sizeof(name) - 1);
	name[sizeof(name) - 1] = '\0';
	for (i = 0; i < sizeof(name) && inFileName[i] != '.'; i++) {
		name[i] = inFileName[i];
	}
	if (inFileName[i] == '.') {
		i++;
	}
	memset(ext, ' ', sizeof(ext) - 1);
	ext[sizeof(ext) - 1] = '\0';
	for (j = 0; j < sizeof(ext); j++) {
		ext[j] = inFileName[i++];
	}
	// Zero out FCB
	memset(dirFcb, 0, sizeof(dirFcb));
	memcpy(dirFcb.name, name, sizeof(dirFcb.name));
	memcpy(dirFcb.ext, ext, sizeof(dirFcb.ext));
	// Use current disk and user
	retVal = initDir(curDisk, curUser, &dirFcb, dmaBuf);
	if (retVal == 0) {
		// Copy first file name to FCB from DMA buffer
		memcpy(&retFcb, dmaBuf, sizeof(struct fcb));
		// Add to linked list
		insertEnd(&head, fcbToFileName(&retFcb));
		// Get the rest of the file names.
		getDir(&dirFcb, dmaBuf, head);
		while (head != NULL) {
			strcpy(dest, head->data);
			changeExt(dest, "RAW");
			convert(head->data, dest, bits);
			head = head->next;
		}
		freeList(head);
	}
}

/*
 * Main function.
 */
int main(int argc, char *argv[]) {
	unsigned bits;
	/* Make sure we have 3 params */
	if (argc == 3) {
		/* Convert bits param to unsigned char */
		sscanf(argv[2], "%u", &bits);
		/* Check bits valid value */
		if (bits == 4 || bits == 2 || bits == 1) {
			processFiles(argv[1], bits);
		} else {
			puts("\nBits value must 4, 2 or 1.");
		}
	} else {
		dispHelp();
	}
	return EXIT_SUCCESS;
}
