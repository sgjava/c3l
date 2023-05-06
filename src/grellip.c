/*
 * C128 CP/M bitmap ellipse abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>

/*
 * Draw ellipse using digital differential analyzer (DDA) method.
 */
void drawEllipse(screen *scr, int xc, int yc, int a, int b, uchar color) {
	long aa = (long) a * a; /* a^2 */
	long bb = (long) b * b; /* b^2 */
	long aa2 = aa << 1; /* 2(a^2) */
	long bb2 = bb << 1; /* 2(b^2) */
	{
		long x = 0;
		long y = b;
		long xbb2 = 0;
		long yaa2 = y * aa2;
		long errVal = -y * aa; /* b^2 x^2 + a^2 y^2 - a^2 b^2 -b^2x */

		while (xbb2 <= yaa2) /* draw octant from top to top right */
		{
			/* Draw octant */
			(scr->setPixel)(scr, xc + x, yc + y, color);
			(scr->setPixel)(scr, xc + x, yc - y, color);
			(scr->setPixel)(scr, xc - x, yc + y, color);
			(scr->setPixel)(scr, xc - x, yc - y, color);
			x += 1;
			xbb2 += bb2;
			errVal += xbb2 - bb;
			if (errVal >= 0) {
				y -= 1;
				yaa2 -= aa2;
				errVal -= yaa2;
			}
		}
	}
	{
		long x = a;
		long y = 0;
		long xbb2 = x * bb2;
		long yaa2 = 0;
		long errVal = -x * bb;
		while (xbb2 > yaa2) /* draw octant from right to top right */
		{
			/* Draw octant */
			(scr->setPixel)(scr, xc + x, yc + y, color);
			(scr->setPixel)(scr, xc + x, yc - y, color);
			(scr->setPixel)(scr, xc - x, yc + y, color);
			(scr->setPixel)(scr, xc - x, yc - y, color);
			y += 1;
			yaa2 += aa2;
			errVal += yaa2 - aa;
			if (errVal >= 0) {
				x -= 1;
				xbb2 -= bb2;
				errVal -= xbb2;
			}
		}
	}
}
