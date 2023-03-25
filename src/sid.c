/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <sid.h>

/*
 * Clear all SID registers.
 */
void clearSid() {
    register ushort i;
    for (i = sidVoice1; i <= sidEnvGen3; i++) {
        outp(i, 0);
    }
}

/*
 * Set master volume and filter select.
 */

void setSidVol(uchar amp, uchar filter) {
    outp(sidVolume, filter | amp);
}

/*
 * Set ADSR envelope.  All ADSR values must be >= 0 and <= 15.
 */

void setSidEnv(ushort voice, uchar attack, uchar decay, uchar sustain,
uchar release) {
    outp(voice + 5, (attack << 4) | decay);
    outp(voice + 6, (sustain << 4) | release);
}

/*
 * Start release cycle.
 */

void setSidRel(ushort Voice, uchar Waveform) {
    outp(Voice + 4, Waveform);
}

/*
 * Set voice frequency.
 */

void setSidFreq(ushort voice, ushort freq) {
    outp(voice, (uchar) freq);
    outp(voice + 1, (uchar) (freq >> 8));
}

/*
 * Start attack, decay, sustain cycle.  Gate bit is not needed.
 */

void setSidAtt(ushort voice, uchar waveform) {
    outp(voice + 4, waveform | sidGate);
}

/*
 * Set pulse waveform width.
 */

void setSidPulWav(ushort voice, ushort width) {
    outp(voice + 2, (uchar) width);
    outp(voice + 3, (uchar) (width >> 8));
}
