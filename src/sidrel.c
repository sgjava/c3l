/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include "hitech.h"
#include "sys.h"

/*
 * Start release cycle.
 */
void setSidRel(ushort Voice, uchar Waveform) {
	outp(Voice + 4, Waveform);
}
