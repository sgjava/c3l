/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <rtc.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Get RTC time as hh:mm:ss.
 */
char* getRtcTime() {
	char *curTime = (char*) malloc(9);
	uchar seconds, minutes, hour;
	/* Check if RTC is available for access */
	while (getRtcReg(rtcRegA) & 0x80)
		;
	seconds = getRtcReg(rtcSeconds);
	minutes = getRtcReg(rtcMinutes);
	hour = getRtcReg(rtcHours);
	sprintf(curTime, "%02d:%02d:%02d", hour, minutes, seconds);
	return curTime;
}
