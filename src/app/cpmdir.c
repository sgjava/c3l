/*
 * C128 CP/M C Library C3L
 *
 * Get CP/M dir.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <cpm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Print the doubly linked list.
 */
void printList(node *head) {
	while (head != NULL) {
		printf("%s\n", head->data);
		head = head->next;
	}
}

int main(void) {
	int retVal, dmaOffset;
	node *head = NULL;
	struct fcb dirFcb, retFcb;
	// FCB is 36 bytes, but only 32 are returned by CPM_FFST and CPM_FNXT calls
	unsigned char dmaBuf[144];
	// Zero out FCB
	memset(dirFcb, 0, sizeof(dirFcb));
	memcpy(dirFcb.name, "????????", sizeof(dirFcb.name));
	memcpy(dirFcb.ext, "???", sizeof(dirFcb.ext));
	// Use A0
	retVal = initDir(0, 0, &dirFcb, dmaBuf);
	if (retVal == 0) {
		// Copy first file name to FCB from DMA buffer
		memcpy(&retFcb, dmaBuf, sizeof(struct fcb));
		// Add to linked list
		insertEnd(&head, fcbToFileName(&retFcb));
		// Get the rest of the file names.
		getDir(&dirFcb, dmaBuf, head);
		printList(head);
		freeList(head);
		return EXIT_SUCCESS;

	}
	return EXIT_FAILURE;
}
