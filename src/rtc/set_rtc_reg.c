/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <rtc.h>
#include <stdlib.h>

/**
 * Set RTC register.
 */
void setRtcReg(const unsigned char reg, const unsigned char value) {
	outp(rtcRegA, reg);
	outp(rtcRegB, value);
}
