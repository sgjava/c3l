/*
 * C128 CP/M C Library C3L
 *
 * Common code.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <stdlib.h>

/*
 * Free memory allocated for the list.
 */
void freeList(const node *head) {
	while (head != NULL) {
		node *temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}
