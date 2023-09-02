/*
 * C128 CP/M CIA functions for demos.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <sys.h>
#include <cia.h>

/*
 * Convert bcd byte to base 10 byte.
 */
uchar bcdToByte(uchar bcd) {
	return ((bcd >> 4) * 10) + (bcd & 0x0f);
}

/*
 Set CIA 2 TOD clock.
 */
void setCiaTod(uchar hour, uchar min, uchar sec, uchar tenth) {
	/* Bit 7 = 0 sets TOD clock */
	outp(cia2+ciaCtrlRegB, inp(cia2+ciaCtrlRegB) & 0x7f);
	/* CIA 2 TOD hour */
	outp(cia2+ciaTodHrs, hour);
	/* CIA 2 TOD minute */
	outp(cia2+ciaTodMin, min);
	/* CIA 2 TOD second */
	outp(cia2+ciaTodSec, sec);
	/* CIA 2 TOD tenth second */
	outp(cia2+ciaTodTen, tenth);
}

/*
 Start CIA 2 timer A in continuous mode using Hz value.
 */
void startTimer(ushort hz) {
	ushort timerA = ciaTimerFreq / hz;
	/* CIA 2 Timer A lo */
	outp(cia2+ciaTimerALo, (uchar) timerA);
	/* CIA 2 Timer A hi */
	outp(cia2+ciaTimerAHi, (uchar) (timerA >> 8));
	/* Start CIA 2 Timer A */
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
}
