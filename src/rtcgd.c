/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <rtc.h>

/*
 * Get RTC date as mm/dd/yyyy.
 */
char *getRtcDate() {
    char *curDate = (char *) malloc(11);
    sprintf(curDate, "%02d/%02d/20%02d", getRtcReg(8), getRtcReg(7),
            getRtcReg(9));
    return curDate;
}
