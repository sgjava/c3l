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
void subjectRemoveObserver(const subject *s, const observer *o) {
	// Find the observer
	for (int i = 0; i < s->count; ++i) {
		if (s->observers[i] == o) {
			// Shift remaining observers
			memmove(&s->observers[i], &s->observers[i + 1], (s->count - i - 1) * sizeof(observer*));
			// Decrease count
			s->count--;
			break;
		}
	}
}
