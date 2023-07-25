/*
 * C128 CP/M C Library C3L
 *
 * C128 text performance comparison.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <hitech.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <vdc.h>
#include <vic.h>

#include "demo.h"

static char *LINE_80 =
		"01234567890123456789012345678901234567890123456789012345678901234567890123456789";
static char *LINE_40 = "0123456789012345678901234567890123456789";
static uchar LINES = 23;

/*
 * Initialize key scan, VIC screen and console.
 */
void initVic(console *con, screen *scr) {
	/* Use ram at end of bank 1 for screen and copy VDC character set just above that */
	initVicScr(scr, 0x7c00, 0x7000);
	initVicScrMode(scr, scrBlack, scrBlack, scrWhite);
	initCon(con, scr);
}

/*
 * Initialize key scan, VDC screen and console.
 */
void initVdc(console *con, screen *scr) {
	initVdcScr(scr, vdcScrMem, vdcChrMem);
	initVdcScrMode(scr, scrBlack, scrBlack, scrWhite);
	initCon(con, scr);
}

/*
 * Restore VIC, VDC registers and CIA for CP/M return.
 */
void done() {
	doneVic();
	doneVdc();
	doneCia();
}

/*
 * CP/M print speed.
 */
ushort cpm(ushort lines) {
	ushort i;
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	initCiaTimer(ciaMs, 0xffff);
	outp(cia2CtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printf(LINE_80);
	}
	outp(cia2CtrlRegA, ciaStopTimer);
	return 0xffff - (inp(cia2TimerBHi) * 256 + inp(cia2TimerBLo));
}

/*
 * VDC print speed.
 */
ushort vdc(console *con, ushort lines) {
	ushort i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	initCiaTimer(ciaMs, 0xffff);
	outp(cia2CtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, LINE_80);
	}
	outp(cia2CtrlRegA, ciaStopTimer);
	return 0xffff - (inp(cia2TimerBHi) * 256 + inp(cia2TimerBLo));
}

/*
 * VIC print speed.
 */
ushort vic(console *con, ushort lines) {
	ushort i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	initCiaTimer(ciaMs, 0xffff);
	outp(cia2CtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, LINE_40);
	}
	outp(cia2CtrlRegA, ciaStopTimer);
	return 0xffff - (inp(cia2TimerBHi) * 256 + inp(cia2TimerBLo));
}

/*
 * Run demo.
 */
void run(console *vicCon, console *vdcCon, ushort cpmPrint) {
	char str[40];
	ushort vdcPrint = vdc(vdcCon, LINES);
	ushort vicPrint = vic(vicCon, LINES);
	clearHomeCon(vicCon);
	sprintf(str, "CP/M printf %04u ms, %04u ms per line", cpmPrint,
			(cpmPrint / LINES));
	printLineCon(vicCon, str);
	sprintf(str, "VDC printCon %04u ms, %04u ms per line", vdcPrint,
			(vdcPrint / LINES));
	printLineCon(vicCon, str);
	sprintf(str, "VIC printCon %04u ms, %04u ms per line", vicPrint,
			(vicPrint * 2) / LINES);
	printLineCon(vicCon, str);
	waitKey(vicCon->scr);
}

main() {
	ushort cpmMs = cpm(LINES);
	/* Program is small enough to use left over bank 1 memory */
	uchar *vicMem = allocVicMem(1);
	/* Create screen structs */
	screen *vicScr = (screen*) malloc(sizeof(screen));
	screen *vdcScr = (screen*) malloc(sizeof(screen));
	/* Create console structs */
	console *vicCon = (console*) malloc(sizeof(console));
	console *vdcCon = (console*) malloc(sizeof(console));
	initCia();
	initVic(vicCon, vicScr);
	initVdc(vdcCon, vdcScr);
	run(vicCon, vdcCon, cpmMs);
	done();
	free(vicScr);
	free(vicCon);
	free(vicMem);
	free(vdcScr);
	free(vdcCon);
}
