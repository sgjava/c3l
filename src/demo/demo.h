/*
 * C128 CP/M graphics abstraction.
 *
 * Demo functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _DEMO_H
#define _DEMO_H

#include <bitmap.h>
#include <console.h>
#include <screen.h>
#include <stdio.h>

extern void waitKey(screen *scr);
extern void readLine(console *con);
extern void keyboard(screen *scr);
extern void runKeyDemo(console *con);
extern char* generateSentence();
extern void runConDemo(console *con, uchar sentences);
extern void runGraphDemo(bitmap *bmp);

#endif
