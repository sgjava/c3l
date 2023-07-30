/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <sid.h>
#include <sys.h>

/*
 * Set master volume and filter select.
 */
void setSidVol(uchar amp, uchar filter) {
	outp(sidVolume, filter | amp);
}
