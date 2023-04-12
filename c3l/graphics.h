/*
 * Generic bitmap graphics functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include	"hitech.h"

extern ushort bmpWidth;
extern ushort bmpHeight;
extern ushort bmpSize;
extern uchar *bmpMem;
extern uchar *bmpColMem;
extern ushort bmpColSize;
extern uchar *bmpChrMem;
extern uchar aspectRatio;
extern void (*setPixel)(ushort, ushort, uchar);
extern void (*clearBmp)(uchar);
extern void (*clearBmpCol)(uchar);
extern void (*drawLineH)(ushort, ushort, ushort, uchar);
extern void (*drawLineV)(ushort, ushort, ushort, uchar);
extern void drawLine(int x0, int y0, int x1, int y1, uchar color);
extern void drawBezier(int x0, int y0, int x1, int y1, int x2, int y2, uchar color);
extern void drawEllipse(int xc, int yc, int a, int b, uchar color);
extern void drawCircle(int xc, int yc, int a, uchar color);
extern void drawRect(int x0, int y0, int x1, int y1, uchar color);
extern void drawSquare(int x, int y, int len, uchar color);
