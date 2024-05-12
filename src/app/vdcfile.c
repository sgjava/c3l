/*
 * C128 CP/M C Library C3L
 *
 * Basline app.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <stdlib.h>
#include <stdio.h>
#include <vdc.h>

#pragma output noprotectmsdos

int main(void) {
	unsigned char *chr = (unsigned char*) malloc(2048);
	printf("Writing VDC character set\n");
	vdcChrMemToFile(0x3000, 256, "default.chr");
	printf("Reading VDC character set\n");
	fileToMem(chr, 2048, "default.chr");
	free(chr);
	return EXIT_SUCCESS;
}
