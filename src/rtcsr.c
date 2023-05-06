/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <rtc.h>
#include <sys.h>

/**
 * Set RTC register.
 */
void setRtcReg(uchar reg, uchar value) {
	outp(rtcRegA, reg);
	outp(rtcRegB, value);
}
