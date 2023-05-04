/*
 * Application helper code.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include	"hitech.h"

#define ciaMs 912 /* ~1 millisecond using CIA microsecond timer */

extern void initCia();
extern void doneCia();
extern void initCiaTimer(ushort timerA, ushort timerB);
extern initVicScrRom(screen *scr, ushort scrMem, uchar bgCol, uchar fgCol, uchar chrCol);
extern doneVic(screen *scr, uchar bgCol, uchar fgCol);
