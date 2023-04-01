/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <rtc.h>

/**
 * Set RTC register.
 */
void setRtcReg(uchar reg, uchar value) {
	outp(rtcRegA, reg);
	outp(rtcRegB, value);
}
