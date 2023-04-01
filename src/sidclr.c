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
