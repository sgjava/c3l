/*
 * C128 CP/M C Library C3L
 *
 * DS12C887 - Real Time Clock demo.
 *
 * See https://github.com/ytmytm/c64-ds12c887
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#pragma output noprotectmsdos

#include <rtc.h>
#include <stdio.h>
#include <stdlib.h>

main() {
	printf("\nDefault mode Binary, 24h, DST\n");
	setRtcMode(rtcDefaultMode);
	printf("Date %02u/%02u/20%02u, Time: %02u:%02u:%02u\n", getRtcReg(rtcMonth), getRtcReg(rtcDay), getRtcReg(rtcYear),
			getRtcReg(rtcHours), getRtcReg(rtcMinutes), getRtcReg(rtcSeconds));
}
