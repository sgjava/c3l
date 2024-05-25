/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <rtc.h>
#include <stdlib.h>

/*
 * Get RTC register.
 */
unsigned char getRtcReg(const unsigned char reg) {
	outp(rtcRegA, reg);
	return inp(rtcRegB);
}
