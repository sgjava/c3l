/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include <stdlib.h>

/*
 * Set voice frequency.
 */
void setSidFreq(unsigned int voice, unsigned int freq) {
	outp(voice, (unsigned char ) freq);
	outp(voice + 1, (unsigned char ) (freq >> 8));
}
