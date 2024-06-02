/*
 * C128 CP/M bitmap ellipse abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>

/*
 * Draw ellipse using the midpoint algorithm. The algorithm works by dividing
 * the ellipse into two halves and drawing each half separately.
 */
void drawEllipse(const bitmap *bmp, const int xc, const int yc, const int a, const int b, const unsigned char color) {
    long a2 = (long) a * a;
    long b2 = (long) b * b;
    long fa2 = 4 * a2, fb2 = 4 * b2;
    long x, y, sigma;

    /* First half */
    for (x = 0, y = b, sigma = 2 * b2 + a2 * (1 - 2 * b); b2 * x <= a2 * y; x++) {
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
    for (x = a, y = 0, sigma = 2 * a2 + b2 * (1 - 2 * a); a2 * y <= b2 * x; y++) {
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
