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
 * Notify all observers of a change.
 */
void subjectNotify(subject* self, void* data) {
    for (int i = 0; i < self->observer_count; ++i) {
    	// Call update on each observer
        self->observers[i]->update(self->observers[i], data);
    }
}
