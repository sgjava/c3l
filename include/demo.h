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

extern void __LIB__ waitKey(const screen *scr);
extern void __LIB__ readLine(const console *con);
extern void __LIB__ keyboard(const screen *scr);
extern void __LIB__ runKeyDemo(const console *con);
extern char __LIB__ *generateSentence();
extern void __LIB__ runConDemo(const console *con, const unsigned char sentences);
extern void __LIB__ runGraphDemo(const bitmap *bmp) ;
extern void __LIB__ runGraphDemoI(const console *con, const bitmap *bmp, const unsigned int code);
extern void __LIB__ runDualDemo(const console *vicCon, const console *vdcCon);
extern void __LIB__ runTextDemo(const console *vicCon, const console *vdcCon, const unsigned int cpmPrintMs, const unsigned int cpmScrollMs, const unsigned int lines);
extern unsigned int __LIB__ cpmPrint(const char *str, const unsigned int lines);
extern unsigned int __LIB__ cpmScroll(const unsigned int lines);
extern void __LIB__ runTextDemo(const console *vicCon, const console *vdcCon, const unsigned int cpmPrintMs, const unsigned int cpmScrollMs, const unsigned int lines) ;

#endif
