/*
 * C128 CP/M text console.
 *
 * Console implementation using fast text functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <hitech.h>
#include <screen.h>

/*
 * Forward reference for function pointer typedefs.
 */
typedef struct console console;

/*
 * We treat the console struct like an object and encapsulate member variables and function pointers that allow polymorphism.
 */
typedef struct console {
	/*
	 * Screen struct.
	 */
	screen *scr;
	/*
	 * Cursor X location.
	 */
	uchar curX;
	/*
	 * Screen height in characters.
	 */
	uchar curY;
};

extern void initCon(console *con, screen *scr);
extern scrollCon(console *con, char *str);
extern printCon(console *con, char *str);

#endif
