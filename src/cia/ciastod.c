/*
 * C128 6526 CIA functions.
 *
 * Set CIA TOD clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 Set CIA 2 TOD clock.
 */
void setCiaTod(ushort cia, uchar hour, uchar min, uchar sec, uchar tenth) {
	/* Bit 7 = 0 sets TOD clock */
	outp(cia+ciaCtrlRegB, inp(cia+ciaCtrlRegB) & 0x7f);
	/* CIA TOD hour */
	outp(cia+ciaTodHrs, hour);
	/* CIA TOD minute */
	outp(cia+ciaTodMin, min);
	/* CIA TOD second */
	outp(cia+ciaTodSec, sec);
	/* CIA TOD tenth second */
	outp(cia+ciaTodTen, tenth);
}
