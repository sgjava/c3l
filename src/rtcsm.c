/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "rtc.h"
#include "hitech.h"

/*
 * Set RTC mode.
 */
void setRtcMode(uchar mode) {
	setRtcReg(rtcMode, mode);
}
