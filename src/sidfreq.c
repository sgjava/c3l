/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "sid.h"
#include "hitech.h"
#include <sys.h>

/*
 * Set voice frequency.
 */
void setSidFreq(ushort voice, ushort freq) {
	outp(voice, (uchar) freq);
	outp(voice + 1, (uchar) (freq >> 8));
}
