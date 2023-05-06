/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include "rtc.h"

/*
 * Get RTC time as hh:mm:ss.
 */
char* getRtcTime() {
	char *curTime = (char*) malloc(9);
	sprintf(curTime, "%02d:%02d:%02d", getRtcReg(rtcHours),
			getRtcReg(rtcMinutes), getRtcReg(rtcSeconds));
	return curTime;
}
