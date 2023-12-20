/*
 * C128 CP/M bitmap ellipse abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <hitech.h>

/*
 * Draw ellipse using the midpoint algorithm. The algorithm works by dividing
 * the ellipse into two halves and drawing each half separately.
 */
void drawEllipse(bitmap *bmp, int xc, int yc, int a, int b, uchar color) {
	int a2 = a * a;
	int b2 = b * b;
	int fa2 = 4 * a2, fb2 = 4 * b2;
	int x, y, sigma;
	/* First half */
	for (x = 0, y = b, sigma = 2 * b2 + a2 * (1 - 2 * b); b2 * x <= a2 * y;
			x++) {
		(bmp->setPixel)(bmp, xc + x, yc + y, color);
		(bmp->setPixel)(bmp, xc - x, yc + y, color);
		(bmp->setPixel)(bmp, xc + x, yc - y, color);
		(bmp->setPixel)(bmp, xc - x, yc - y, color);
		if (sigma >= 0) {
			sigma += fa2 * (1 - y);
			y--;
		}
		sigma += b2 * ((4 * x) + 6);
	}
	/* Second half */
	for (x = a, y = 0, sigma = 2 * a2 + b2 * (1 - 2 * a); a2 * y <= b2 * x;
			y++) {
		(bmp->setPixel)(bmp, xc + x, yc + y, color);
		(bmp->setPixel)(bmp, xc - x, yc + y, color);
		(bmp->setPixel)(bmp, xc + x, yc - y, color);
		(bmp->setPixel)(bmp, xc - x, yc - y, color);
		if (sigma >= 0) {
			sigma += fb2 * (1 - x);
			x--;
		}
		sigma += a2 * ((4 * y) + 6);
	}
}
