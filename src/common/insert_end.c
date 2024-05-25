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
 * Insert a node at the end of the list.
 */
void insertEnd(const node **head, const char *data) {
	node *newNode = createNode(data);
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	node *temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}
