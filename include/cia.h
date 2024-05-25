/*
 * C128 6526 CIA.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _CIA_H
#define _CIA_H

#include <sys/compiler.h>

#define cia1         0xdc00   /* Complex interface adapter #1 */
#define cia2         0xdd00   /* Complex interface adapter #2 */

#define ciaDataA     0x00     /* Port A data I/O register */
#define ciaDataB     0x01     /* Port B data I/O register */
#define ciaDdrA      0x02     /* Port A data direction register */
#define ciaDdrB      0x03     /* Port B data direction register */
#define ciaTimerALo  0x04     /* Timer A latch/counter (low byte) */
#define ciaTimerAHi  0x05     /* Timer A latch/counter (high byte) */
#define ciaTimerBLo  0x06     /* Timer B latch/counter (low byte) */
#define ciaTimerBHi  0x07     /* Timer B latch/counter (high byte) */
#define ciaTodTen    0x08     /* Time-of-day clock (1/10 seconds) */
#define ciaTodSec    0x09     /* Time-of-day clock (seconds) */
#define ciaTodMin    0x0a     /* Time-of-day clock (minutes) */
#define ciaTodHrs    0x0b     /* Time-of-day clock (hours) */
#define ciaSerial    0x0c     /* Serial data register */
#define ciaIcr       0x0d     /* Interrupt control register */
#define ciaCtrlRegA  0x0e     /* Control register A */
#define ciaCtrlRegB  0x0f     /* Control register B */

#define vicExtKey    0xd02f   /* Extended keyboard scan register on the VIC */

#define ciaTimerFreq 1022730L /* CIA timer freq */
#define ciaEnableIrq 0x82     /* Enable cia irq */
#define ciaClearIcr  0x7f     /* Clear all cia irq enable bits */
#define ciaPots      0xc0     /* Set bits 6 and 7 to output */
#define ciaCpuCont   0x11     /* Load latch, start timer, count cpu cycles continuous */
#define ciaCpuOne    0x19     /* Load latch, start timer, count cpu cycles one shot */
#define ciaCountA    0x51     /* Load latch, start timer, count timer A */
#define ciaStopTimer 0x00     /* Stop timer */

#define ciaNone      0x1f     /* Joy stick direction masks */
#define ciaFire      0x10
#define ciaUp        0x01
#define ciaDown      0x02
#define ciaLeft      0x04
#define ciaRight     0x08
#define ciaUpLeft    0x05
#define ciaUpRight   0x09
#define ciaDownLeft  0x06
#define ciaDownRight 0x0a

#define ciaPotsPort1 0x40     /* 4066 analog switch settings for CIA 1 */
#define ciaPotsPort2 0x80

#define ciaMs 1022            /* ~1 millisecond using CIA microsecond timer */

extern unsigned char __LIB__ getKeyCol(const unsigned char keyVal);
extern unsigned char __LIB__ getLsKeyCol(const unsigned char keyVal);
extern unsigned char __LIB__ getRsKeyCol(const unsigned char keyVal);
extern unsigned char __LIB__ getKey(const unsigned char keyRow);
extern void __LIB__ getKeys(const unsigned char* ciaKeyScan);
extern unsigned char __LIB__ decodeKey();
extern void __LIB__ initCia();
extern void __LIB__ doneCia();
extern void __LIB__ startTimerAB(const unsigned int cia, const unsigned int timerA, const unsigned int timerB, const unsigned char latch);
extern void __LIB__ setCiaTod(const unsigned int cia, const unsigned char hour, const unsigned char min, const unsigned char sec, const unsigned char tenth);
extern void __LIB__ startTimerA(const unsigned int cia, const unsigned int hz, const unsigned char latch);
extern void __LIB__ startTimerB(const unsigned int cia, const unsigned int hz, const unsigned char latch);
extern unsigned char __LIB__ getJoystick1();
extern unsigned char __LIB__ getJoystick2();
extern unsigned long __LIB__ todToMs(const unsigned int cia);
extern unsigned char __LIB__ bcdToByte(const unsigned char bcd);

#endif
