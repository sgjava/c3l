/*
 * C128 CP/M C Library C3L
 *
 * Common code.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <stdlib.h>
#include <string.h>

/*
 * Create a new node. Returns NULL on failure.
 */
node* createNode(const char *data) {
	node *newNode = (node*) malloc(sizeof(node));
	if (newNode != NULL) {
		// Allocate memory for the string and copy data
		newNode->data = strdup(data);
		newNode->prev = NULL;
		newNode->next = NULL;
	}
	return newNode;
}
