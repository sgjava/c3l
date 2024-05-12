/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include <stdlib.h>

/*
 * Set pulse waveform width.
 */
void setSidPulWav(unsigned int voice, unsigned int width) {
	outp(voice + 2, (unsigned char ) width);
	outp(voice + 3, (unsigned char ) (width >> 8));
}
