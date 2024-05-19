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
void subjectAddObserver(subject* s, observer* o) {
	// If array is full
    if (s->count >= s->capacity) {
    	// Double the capacity
        s->capacity *= 2;
        // Reallocate memory
        s->observers = (observer**)realloc(s->observers, s->capacity * sizeof(observer*));
    }
    // Add the new observer
    s->observers[s->count++] = o;
}
