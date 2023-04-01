/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <sid.h>

/*
 * Set pulse waveform width.
 */
void setSidPulWav(ushort voice, ushort width) {
    outp(voice + 2, (uchar) width);
    outp(voice + 3, (uchar) (width >> 8));
}
