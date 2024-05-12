/*
 * C128 CP/M C Library C3L
 *
 * Common code..
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _COMMON_H
#define _COMMON_H

#include <sys/compiler.h>

/*
 * Forward reference.
 */
typedef struct node node;

/*
 * Define the structure for a node in the doubly linked list.
 */
typedef struct node {
	char *data; // Pointer to hold the string
	struct node *prev; // Pointer to the previous node
	struct node *next; // Pointer to the next node
};

extern node __LIB__ *createNode(char *data);
extern void __LIB__ insertEnd(node **head, char *data);
extern void __LIB__ freeList(node *head);
extern int __LIB__ initDir(int login, int user, struct fcb *fcb, unsigned char dmaBuf[]);
extern int __LIB__ getDir(struct fcb *fcb, unsigned char dmaBuf[], node *head);
extern char __LIB__ *fcbToFileName(struct fcb *fcb);
extern void __LIB__ fileToMem(unsigned char *mem, unsigned int len, char *fileName);

#endif
