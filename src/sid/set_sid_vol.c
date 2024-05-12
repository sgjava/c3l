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
void setSidVol(unsigned char amp, unsigned char filter) {
	outp(sidVolume, filter | amp);
}
