/*
 * C128 CP/M wait for return to be pressed.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <screen.h>
#include <demo.h>

/*
 * Wait for Return key to be pressed.
 */
void waitKey(const screen *scr) {
	(scr->printCol)(scr, 0, scr->scrHeight - 1, scrYellow, "Press Return");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
}
