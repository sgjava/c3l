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
	// Pointer to hold the string
	char *data;
	// Pointer to the previous node
	struct node *prev;
	// Pointer to the next node
	struct node *next;
};

/*
 * Forward reference.
 */
typedef struct observer observer;

/*
 * Define a function pointer type for the update method that observers must implement.
 */
struct observer {
	void (*update)(observer *o);
};

/*
 * The subject needs to maintain a list of observers and provide methods to add, remove, and notify them.
 */
typedef struct {
	observer **observers;
	int count;
	int capacity;
} subject;

extern node __LIB__* createNode(char *data);
extern void __LIB__ insertEnd(node **head, char *data);
extern void __LIB__ freeList(node *head);
extern int __LIB__ initDir(int login, int user, struct fcb *fcb, unsigned char dmaBuf[]);
extern int __LIB__ getDir(struct fcb *fcb, unsigned char dmaBuf[], node *head);
extern char __LIB__* fcbToFileName(struct fcb *fcb);
extern void __LIB__ fileToMem(unsigned char *mem, unsigned int len, char *fileName);
extern void __LIB__ subjectInit(subject *s);
extern void __LIB__ subjectAddObserver(subject *s, observer *o);
extern void __LIB__ subjectRemoveObserver(subject *s, observer *o);
extern void __LIB__ subjectNotify(subject *s);

#endif
