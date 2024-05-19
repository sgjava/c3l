/*
 * C128 CP/M C Library C3L
 *
 * Observer pattern test.
 *
 * The observer pattern is a design pattern used to establish a one-to-many dependency between objects so that when one object (the
 *  subject) changes state, all its dependents (observers) are notified and updated automatically. This pattern is highly useful in various
 *  scenarios, particularly those involving dynamic relationships and decoupling components.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <common.h>

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024

// Observer payload
typedef struct {
	// Function to call
	observer o;
	// Data
	int data;
} payload;

/*
 * Update function for the payload.
 */
void update1(observer *o) {
	// Cast to payload
	payload *p = (payload*) o;
	// Handle the update with data
	printf("Payload received update with data: %d\n", p->data);
}

/*
 * Update function for the payload.
 */
void update2(observer *o) {
	// Cast to payload
	payload *p = (payload*) o;
	// Handle the update with data
	printf("Payload received update with data: %d\n", p->data);
}

int main(void) {
	subject s;
	payload observer1, observer2;
	// Initialize the subject
	subjectInit(&s);
	// Configure update
	observer1.o.update = update1;
	observer1.data = 1;
	subjectAddObserver(&s, (observer*) &observer1);
	observer2.o.update = update2;
	observer2.data = 2;
	subjectAddObserver(&s, (observer*) &observer2);
	// Notify all observers
	subjectNotify(&s);
	free(s.observers);
	return EXIT_SUCCESS;
}
