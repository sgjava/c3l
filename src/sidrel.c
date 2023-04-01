/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <sid.h>

/*
 * Start release cycle.
 */
void setSidRel(ushort Voice, uchar Waveform) {
    outp(Voice + 4, Waveform);
}
