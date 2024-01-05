/*
 * C128 6526 CIA functions.
 *
 * Read joystick 1.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 * Read joystick 1. Assuming CIA 1 DDR B is set to 0x00.
 */
uchar getJoystick1() {
	return inp(cia1+ciaDataB) & ciaNone;
}
