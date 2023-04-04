/*
 * Generic text based screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include	"hitech.h"

extern uchar scrWidth;
extern uchar scrHeight;
extern ushort scrSize;
extern uchar *scrMem;
extern uchar *scrColMem;
extern uchar *chrMem;
extern void (*clearScr)( uchar);
extern void (*clearScrCol)( uchar);
extern void (*print)( uchar, uchar, char *);
extern void (*printCol)( uchar, uchar, uchar, char *);
extern char *asciiToPet(char *str);

