/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include <stdlib.h>

/*
 * Clear all SID registers.
 */
void clearSid() {
	unsigned int i;
	for (i = sidVoice1; i <= sidEnvGen3; i++) {
		outp(i, 0);
	}
}
