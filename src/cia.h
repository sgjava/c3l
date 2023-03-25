/*
 * C128 6526 CIA.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#define cia1DataA    0xdc00 /* Port A data I/O register */
#define cia1DataB    0xdc01 /* Port B data I/O register */
#define cia1DdrA     0xdc02 /* Port A data direction register */
#define cia1DdrB     0xdc03 /* Port B data direction register */
#define cia1TimerALo 0xdc04 /* Timer A latch/counter (low byte) */
#define cia1TimerAHi 0xdc05 /* Timer A latch/counter (high byte) */
#define cia1TimerBLo 0xdc06 /* Timer B latch/counter (low byte) */
#define cia1TimerBHi 0xdc07 /* Timer B latch/counter (high byte) */
#define cia1TodTen   0xdc08 /* Time-of-day dock (1/10 seconds) */
#define cia1TodSec   0xdc09 /* Time-of-day clock (seconds) */
#define cia1TodMin   0xdc0a /* Time-of-day dock (minutes) */
#define cia1TodHrs   0xdc0b /* Time-of-day dock (hours) */
#define cia1Serial   0xdc0c /* Serial data register */
#define cia1Icr      0xdc0d /* Interrupt control register */
#define cia1CtrlRegA 0xdc0e /* Control register A */
#define cia1CtrlRegB 0xdc0f /* Control register B */

#define cia2DataA    0xdd00 /* Port A data I/O register */
#define cia2DataB    0xdd01 /* Port B data I/O register */
#define cia2DdrA     0xdd02 /* Port A data direction register */
#define cia2DdrB     0xdd03 /* Port B data direction register */
#define cia2TimerALo 0xdd04 /* Timer A latch/counter (low byte) */
#define cia2TimerAHi 0xdd05 /* Timer A latch/counter (high byte) */
#define cia2TimerBLo 0xdd06 /* Timer B latch/counter (low byte) */
#define cia2TimerBHi 0xdd07 /* Timer B latch/counter (high byte) */
#define cia2TodTen   0xdd08 /* Time-of-day dock (1/10 seconds) */
#define cia2TodSec   0xdd09 /* Time-of-day clock (seconds) */
#define cia2TodMin   0xdd0a /* Time-of-day dock (minutes) */
#define cia2TodHrs   0xdd0b /* Time-of-day dock (hours) */
#define cia2Serial   0xdd0c /* Serial data register */
#define cia2Icr      0xdd0d /* Interrupt control register */
#define cia2CtrlRegA 0xdd0e /* Control register A */
#define cia2CtrlRegB 0xdd0f /* Control register B */

#define ciaTimerFreq 1022730L /* CIA timer freq */
#define ciaClearIcr  0x7F     /* Clear all cia irq enable bits */
#define ciaCPUCont   0x11     /* Load latch, start timer, count cpu cycles continuous */
#define ciaCPUOne    0x19     /* Load latch, start timer, count cpu cycles one shot */
#define ciaCountA    0x51     /* Load latch, start timer, count timer A */

#define ciaNone      0x1F     /* Joy stick direction masks */
#define ciaFire      0x10
#define ciaUp        0x01
#define ciaDown      0x02
#define ciaLeft      0x04
#define ciaRight     0x08
#define ciaUpLeft    0x05
#define ciaUpRight   0x09
#define ciaDownLeft  0x06
#define ciaDownRight 0x0A

#define ciaPotsPort1 0x40     /* 4066 analog switch settings for CIA 1 */
#define ciaPotsPort2 0x80

extern uchar getKeyCol(uchar keyVal);
extern uchar getLsKeyCol(uchar keyVal);
extern uchar getRsKeyCol(uchar keyVal);
extern uchar getKey(uchar keyRow);
extern uchar *getKeys();
extern uchar decodeKey();

