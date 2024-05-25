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
void subjectNotify(const subject* s) {
    for (int i = 0; i < s->count; ++i) {
    	// Call update on each observer
        s->observers[i]->update(s->observers[i]);
    }
}
