/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <sys.h>
#include <stdio.h>
#include <hitech.h>
#include <rtc.h>

/**
 * Set RTC register.
 */
void setRtcReg(uchar reg, uchar value) {
    outp(rtcRegA, reg);
    outp(rtcRegB, value);
}

/*
 * Get RTC register.
 */
uchar getRtcReg(uchar reg) {
    outp(rtcRegA, reg);
    return inp(rtcRegB);
}

/*
 * Set RTC mode.
 */
void setRtcMode(uchar mode) {
    setRtcReg(11, mode);
}

/*
 * Get RTC time as hh:mm:ss.
 */
char *getRtcTime() {
    char *curTime = (char *) malloc(9);
    sprintf(curTime, "%02d:%02d:%02d", getRtcReg(4), getRtcReg(2),
            getRtcReg(0));
    return curTime;
}

/*
 * Get RTC date as mm/dd/yyyy.
 */
char *getRtcDate() {
    char *curDate = (char *) malloc(11);
    sprintf(curDate, "%02d/%02d/20%02d", getRtcReg(8), getRtcReg(7),
            getRtcReg(9));
    return curDate;
}
