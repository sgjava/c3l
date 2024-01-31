/*
 * C128 CP/M graphics abstraction.
 *
 * Demo functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _DEMO_H
#define _DEMO_H

#include <bitmap.h>
#include <console.h>

extern void waitKey(screen *scr);
extern void readLine(console *con);
extern void keyboard(screen *scr);
extern void runKeyDemo(console *con);
extern char* generateSentence();
extern void runConDemo(console *con, uchar sentences);
extern void runGraphDemo(bitmap *bmp);
extern void runGraphDemoI(console *con, bitmap *bmp, ushort code);
extern void runDualDemo(console *vicCon, console *vdcCon);
extern void runTextDemo(console *vicCon, console *vdcCon, ushort cpmPrintMs, ushort cpmScrollMs, ushort lines);
extern ushort cpmPrint(char *str, ushort lines);
extern ushort cpmScroll(ushort lines);
extern void playPcm4Sid(uchar *buffer, ushort len);
extern void playPcm1Sid(uchar *buffer, ushort len, uchar vol);
extern void playPcm2Sid(uchar *buffer, ushort len);
extern ulong todToMs(ushort cia);
extern uchar bcdToByte(uchar bcd);

/*
 * Official ARPAbet has 39 phonemes
 */
#define PHONEMES 39

typedef char arpabetName[PHONEMES][3];

/*
 * Forward reference.
 */
typedef struct phonemes phonemes;

/*
 * Output file header.
 */
typedef struct phonemes {
	/*
	 * Play back Hz.
	 */
	ushort hz;
	/*
	 * Sample width in bits.
	 */
	uchar bits;
	/*
	 * ARPAbet name
	 */
	arpabetName name;
	/*
	 * Phoneme length.
	 */
	ushort arpabetLen[PHONEMES];
};

#endif
