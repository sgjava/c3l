/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include <stdlib.h>

/*
 * Set master volume and filter select.
 */
void setSidVol(const unsigned char amp, const unsigned char filter) {
	outp(sidVolume, filter | amp);
}
