/*
 * C128 CP/M C Library C3L
 *
 * Common code.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <cpm.h>
#include <stdlib.h>
#include <string.h>

/*
 * Convert name and ext from FCB to normal 8.3 file name string.
 */
char* fcbToFileName(struct fcb *fcb) {
	int i, j;
	// Allocate memory for 8.3 style file name
	char *fileName = (char*) malloc(13 * sizeof(char));
	if (fileName == NULL) {
		// Memory allocation failed
		return NULL;
	}
	// Initialize the allocated memory to spaces
	memset(fileName, ' ', 12);
	// Copy name from FCB into fileName
	for (i = 0; i < 8 && fcb->name[i] != ' '; i++) {
		fileName[i] = fcb->name[i];
	}
	fileName[i++] = '.';
	// Copy extension from FCB into fileName
	for (j = 0; j < 3 && fcb->ext[j] != ' '; j++) {
		fileName[i++] = fcb->ext[j];
	}
	// Ext starts with space, so terminate string
	if (j == 0) {
		fileName[--i] = '\0';
	} else {
		fileName[i] = '\0';
	}
	return fileName;
}
