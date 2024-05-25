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
	const screen *scr;
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

extern void __LIB__ initCon(const console *con, const screen *scr);
extern void __LIB__ scrollCon(const console *con, const char *str);
extern void __LIB__ printCon(const console *con, const char *str);
extern void __LIB__ printLineCon(const console *con, const char *str);
extern char __LIB__ *readLineCon(const console *con, const unsigned char len);
extern unsigned int __LIB__ offsetCon(const console *con);
extern void __LIB__ setCurCon(const console *con, const unsigned int offset);
extern void __LIB__ printWrapCon(const console *con, const char *str);
extern void __LIB__ clearHomeCon(const console *con);

#endif
