/*
 * C128 CP/M C Library C3L
 *
 * Common code.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <common.h>
#include <string.h>

/*
 * Remove an observer from the subject.
 */
void subjectRemoveObserver(subject* self, observer* o) {
	// Find the observer
    for (int i = 0; i < self->observer_count; ++i) {
        if (self->observers[i] == o) {
        	// Shift remaining observers
            memmove(&self->observers[i], &self->observers[i + 1], (self->observer_count - i - 1) * sizeof(observer*));
            // Decrease count
            self->observer_count--;
            break;
        }
    }
}
