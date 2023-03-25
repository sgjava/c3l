/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#define rtcRegA 0xde00 /* Register A address */
#define rtcRegB 0xde01 /* Register B address */

extern void setRtcReg(uchar reg, uchar value);
extern uchar getRtcReg(uchar reg);
extern void setRtcMode(uchar mode);
extern char *getRtcTime();
extern char *getRtcDate();

