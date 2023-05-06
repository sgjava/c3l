/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <rtc.h>

/*
 * Set RTC mode.
 */
void setRtcMode(uchar mode) {
	setRtcReg(rtcMode, mode);
}
