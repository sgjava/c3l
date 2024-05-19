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
 * Initialize the subject.
 */
void subjectInit(subject* s) {
	// No observers initially
    s->count = 0;
    // Set initial capacity
    s->capacity = 4;
    // Allocate memory
    s->observers = (observer**)malloc(s->capacity * sizeof(observer*));
}
