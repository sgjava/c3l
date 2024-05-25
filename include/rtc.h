/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _RTC_H
#define _RTC_H

#include <sys/compiler.h>

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

extern void __LIB__ setRtcReg(const unsigned char reg, const unsigned char value);
extern unsigned char __LIB__ getRtcReg(const unsigned char reg);
extern void __LIB__ setRtcMode(const unsigned char mode);

#endif
