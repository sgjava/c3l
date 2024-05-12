/*
 * C128 6526 CIA functions.
 *
 * Read joystick 2.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 * Read joystick 2. Assuming CIA 1 DDR A is set to 0xff.
 */
unsigned char getJoystick2() {
	return inp(cia1+ciaDataA) & ciaNone;
}
