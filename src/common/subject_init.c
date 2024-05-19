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
void subjectInit(subject* self) {
	// No observers initially
    self->observer_count = 0;
    // Set initial capacity
    self->observer_capacity = 4;
    // Allocate memory
    self->observers = (observer**)malloc(self->observer_capacity * sizeof(observer*));
}
