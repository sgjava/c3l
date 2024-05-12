/*
 * C128 CP/M text abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <stdio.h>

/*
 * Read binary file into memory.
 */
void fileToMem(unsigned char *mem, unsigned int len, char *fileName) {
	FILE *file;
	if ((file = fopen(fileName, "rb")) != NULL) {
		fread(mem, sizeof(unsigned char), len, file);
		fclose(file);
	}
}
