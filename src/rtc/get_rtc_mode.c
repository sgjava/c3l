/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <rtc.h>

/*
 * Set RTC mode.
 */
void setRtcMode(unsigned char mode) {
	setRtcReg(rtcMode, mode);
}
