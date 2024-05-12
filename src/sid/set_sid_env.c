/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include <stdlib.h>

/*
 * Set ADSR envelope.  All ADSR values must be >= 0 and <= 15.
 */
void setSidEnv(unsigned int voice, unsigned char attack, unsigned char decay,
		unsigned char sustain, unsigned char release) {
	outp(voice + 5, (attack << 4) | decay);
	outp(voice + 6, (sustain << 4) | release);
}
