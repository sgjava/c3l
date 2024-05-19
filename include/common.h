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

/*
 * Forward reference.
 */
typedef struct observer observer;

/*
 * Define a function pointer type for the update method that observers must implement.
 */
struct observer {
    void (*update)(observer* self, void* data);
};

/*
 * The subject needs to maintain a list of observers and provide methods to add, remove, and notify them.
 */
typedef struct {
    observer** observers;
    int observer_count;
    int observer_capacity;
} subject;

extern node __LIB__ *createNode(char *data);
extern void __LIB__ insertEnd(node **head, char *data);
extern void __LIB__ freeList(node *head);
extern int __LIB__ initDir(int login, int user, struct fcb *fcb, unsigned char dmaBuf[]);
extern int __LIB__ getDir(struct fcb *fcb, unsigned char dmaBuf[], node *head);
extern char __LIB__ *fcbToFileName(struct fcb *fcb);
extern void __LIB__ fileToMem(unsigned char *mem, unsigned int len, char *fileName);
extern void __LIB__ subjectInit(subject* self);
extern void __LIB__ subjectAddObserver(subject* self, observer* o) ;
extern void __LIB__ subjectRemoveObserver(subject* self, observer* o);
extern void __LIB__ subjectNotify(subject* self, void* data) ;

#endif
