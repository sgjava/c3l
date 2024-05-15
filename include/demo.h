/*
 * C128 CP/M graphics abstraction.
 *
 * Demo functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _DEMO_H
#define _DEMO_H

#include <sys/compiler.h>
#include <bitmap.h>
#include <console.h>

extern void __LIB__ waitKey(screen *scr);
extern void __LIB__ readLine(console *con);
extern void __LIB__ keyboard(screen *scr);
extern void __LIB__ runKeyDemo(console *con);
extern char __LIB__ *generateSentence();
extern void __LIB__ runConDemo(console *con, unsigned char sentences);
extern void __LIB__ runGraphDemo(bitmap *bmp);
extern void __LIB__ runGraphDemoI(console *con, bitmap *bmp, unsigned int code);
extern void __LIB__ runDualDemo(console *vicCon, console *vdcCon);
extern void __LIB__ runTextDemo(console *vicCon, console *vdcCon, unsigned int cpmPrintMs, unsigned int cpmScrollMs, unsigned int lines);
extern unsigned int __LIB__ cpmPrint(char *str, unsigned int lines);
extern unsigned int __LIB__ cpmScroll(unsigned int lines);
extern void __LIB__ runTextDemo(console *vicCon, console *vdcCon, unsigned int cpmPrintMs, unsigned int cpmScrollMs, unsigned int lines) ;

#endif
