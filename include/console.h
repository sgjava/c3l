/*
 * C128 CP/M text console.
 *
 * Console implementation using fast text functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <sys/compiler.h>
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
	unsigned char curX;
	/*
	 * Screen height in characters.
	 */
	unsigned char curY;
	/*
	 * Cursor on.
	 */
	unsigned char curOn;
	/*
	 * Cursor character.
	 */
	unsigned char curChar;
	/*
	 * Color on.
	 */
	unsigned char colorOn;
	/*
	 * Character color.
	 */
	unsigned char color;
};

extern void __LIB__ initCon(console *con, screen *scr);
extern void __LIB__ scrollCon(console *con, char *str);
extern void __LIB__ printCon(console *con, char *str);
extern void __LIB__ printLineCon(console *con, char *str);
extern char __LIB__ *readLineCon(console *con, unsigned char len);
extern unsigned int __LIB__ offsetCon(console *con);
extern void __LIB__ setCurCon(console *con, unsigned int offset);
extern void __LIB__ printWrapCon(console *con, char *str);
extern void __LIB__ clearHomeCon(console *con);

#endif
