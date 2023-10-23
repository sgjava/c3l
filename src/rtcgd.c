/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <rtc.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Get RTC date as mm/dd/yyyy.
 */
char* getRtcDate() {
	char *curDate = (char*) malloc(11);
	/* Check if RTC is available for access */
	while (getRtcReg(rtcRegA) & 0x80)
		;
	sprintf(curDate, "%02d/%02d/20%02d", getRtcReg(rtcMonth), getRtcReg(rtcDay),
			getRtcReg(rtcYear));
	return curDate;
}
