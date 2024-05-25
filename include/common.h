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
	void (*update)(const observer *o);
};

/*
 * The subject needs to maintain a list of observers and provide methods to add, remove, and notify them.
 */
typedef struct {
	const observer **observers;
	int count;
	int capacity;
} subject;

extern node __LIB__* createNode(const char *data);
extern void __LIB__ insertEnd(const node **head, const char *data);
extern void __LIB__ freeList(const node *head);
extern int __LIB__ initDir(const int login, const int user, const struct fcb *fcb, const unsigned char dmaBuf[]);
extern int __LIB__ getDir(const struct fcb *fcb, const unsigned char dmaBuf[], const node *head);
extern char __LIB__* fcbToFileName(const struct fcb *fcb);
extern void __LIB__ fileToMem(const unsigned char *mem, const unsigned int len, const char *fileName);
extern void __LIB__ subjectInit(const subject *s);
extern void __LIB__ subjectAddObserver(const subject *s, const observer *o);
extern void __LIB__ subjectRemoveObserver(const subject *s, const observer *o);
extern void __LIB__ subjectNotify(const subject *s);

#endif
