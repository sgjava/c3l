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
 * Add an observer to the subject.
 */
void subjectAddObserver(subject* self, observer* o) {
	// If array is full
    if (self->observer_count >= self->observer_capacity) {
    	// Double the capacity
        self->observer_capacity *= 2;
        // Reallocate memory
        self->observers = (observer**)realloc(self->observers, self->observer_capacity * sizeof(observer*));
    }
    // Add the new observer
    self->observers[self->observer_count++] = o;
}
