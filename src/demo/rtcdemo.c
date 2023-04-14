/*
 * C128 CP/M C Library C3L
 *
 * DS12C887 - Real Time Clock demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <stdio.h>
#include "rtc.h"

main() {
	char *dateStr, *timeStr;
	printf("Default mode Binary, 24h, DST\n");
	setRtcMode(rtcDefaultMode);
	dateStr = getRtcDate();
	timeStr = getRtcTime();
	printf("Date: %s, Time: %s\n",dateStr,timeStr);
	free(dateStr);
	free(timeStr);
}
