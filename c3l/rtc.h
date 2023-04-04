/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include	"hitech.h"

#define rtcRegA      0xde00 /* Register A address */
#define rtcRegB      0xde01 /* Register B address */
#define rtcSeconds      0x0 /* Seconds */
#define rtcMinutes      0x2 /* Minutes */
#define rtcHours        0x4 /* Hours */
#define rtcDay          0x7 /* Day */
#define rtcMonth        0x8 /* Month */
#define rtcYear         0x9 /* Year */
#define rtcMode         0xb /* Mode */
#define rtcDefaultMode  0x87 /* Binary, 24h, DST */

extern void setRtcReg(uchar reg, uchar value);
extern uchar getRtcReg(uchar reg);
extern void setRtcMode(uchar mode);
extern char *getRtcTime();
extern char *getRtcDate();
