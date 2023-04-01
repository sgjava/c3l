/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <sid.h>

/*
 * Set master volume and filter select.
 */
void setSidVol(uchar amp, uchar filter) {
    outp(sidVolume, filter | amp);
}
