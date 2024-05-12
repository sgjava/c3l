/*
 * C128 CP/M C Library C3L
 *
 * Common code.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <cpm.h>
#include <string.h>

/*
 * Retrieve directory entries after initDir called.
 */
int getDir(struct fcb *fcb, unsigned char dmaBuf[], node *head) {
	int retVal, dmaOffset;
	struct fcb retFcb;
	// Prime the pump
	retVal = bdos(CPM_FNXT, &fcb);
	while (retVal > -1) {
		dmaOffset = retVal * 32;
		memcpy(&retFcb, &dmaBuf[dmaOffset], sizeof(struct fcb));
		// Add to linked list
		insertEnd(&head, fcbToFileName(&retFcb));
		retVal = bdos(CPM_FNXT, &fcb);
	}
	return retVal;
}
