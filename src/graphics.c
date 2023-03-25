/*
 * C128 CP/M graphics abstraction.
 *
 * Graphics abstraction uses function pointers to drive the graphics, thus the
 * same code will work on the VIC and VDC. Technically this code would work
 * with other graphic displays as well. You just need to implement the functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>

/*
 * Bitmap memory location.
 */
uchar *bmpMem;

/*
 * Bitmap size in bytes.
 */
ushort bmpSize;

/*
 * Bitmap color location.
 */
uchar *bmpColMem;

/*
 * Bitmap color size.
 */
ushort bmpColSize;

/*
 * Bitmap character set location.
 */
uchar *bmpChrMem;

/*
 * Aspect ratio used by circle and square functions.
 */
uchar aspectRatio;

/*
 * Set pixel.
 */
void (*setPixel)(ushort, ushort);

/*
 * Clear pixel.
 */
void (*clearPixel)(ushort, ushort);

/*
 * Clear bitmap.
 */
void (*clearBmp)(uchar);

/*
 * Clear bitmap color.
 */
void (*clearBmpCol)(uchar);

/*
 * Draw horizontal line.
 */
void (*drawLineH)(ushort, ushort, ushort, uchar);

/*
 * Draw vertical line.
 */
void (*drawLineV)(ushort, ushort, ushort, uchar);
