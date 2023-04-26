/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sid.h>
#include "hitech.h"
#include "sys.h"

/*
 * Start attack, decay, sustain cycle.  Gate bit is not needed.
 */
void setSidAtt(ushort voice, uchar waveform) {
	outp(voice + 4, waveform | sidGate);
}
