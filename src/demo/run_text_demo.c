/*
 * C128 CP/M text performance demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <demo.h>

/*
 * Get elapsed time from CIA 2.
 */
unsigned int elapsedMs() {
	return 0xffff - (inp(cia2 + ciaTimerBHi) * 256 + inp(cia2 + ciaTimerBLo));
}

/*
 * CP/M print speed.
 */
unsigned int cpmPrint(const char *str, const unsigned int lines) {
	unsigned int i;
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printf(str);
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * CP/M print speed.
 */
unsigned int cpmScroll(const unsigned int lines) {
	unsigned int i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printf("\n");
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VDC print speed.
 */
unsigned int vdcPrint(const console *con, const char *str, const unsigned int lines) {
	unsigned int i;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VDC scroll speed.
 */
unsigned int vdcScroll(const console *con, const unsigned int lines) {
	unsigned int i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VIC print speed.
 */
unsigned int vicPrint(const console *con, const char *str, const unsigned int lines) {
	unsigned int i;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VIC scroll speed.
 */
unsigned int vicScroll(const console *con, const unsigned int lines) {
	unsigned int i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VDC color print speed.
 */
unsigned int vdcColor(const console *con, const char *str, const unsigned int lines) {
	unsigned int i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * VDC color scroll speed.
 */
unsigned int vdcColorScroll(const console *con, const unsigned int lines) {
	unsigned int i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * VIC color print speed.
 */
unsigned int vicColor(const console *con, const char *str, const unsigned int lines) {
	unsigned int i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * VIC color scroll speed.
 */
unsigned int vicColorScroll(const console *con, const unsigned int lines) {
	unsigned int i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * Run demo.
 */
void runTextDemo(const console *vicCon, const console *vdcCon, const unsigned int cpmPrintMs,
		const unsigned int cpmScrollMs, const unsigned int lines) {
	static char *LINE_80 =
			"01234567890123456789012345678901234567890123456789012345678901234567890123456789";
	static char *LINE_40 = "0123456789012345678901234567890123456789";
	char str[41];
	unsigned int vdcPrintMs = vdcPrint(vdcCon, LINE_80, lines);
	unsigned int vdcScrollMs = vdcScroll(vdcCon, lines);
	unsigned int vicPrintMs = vicPrint(vicCon, LINE_40, lines);
	unsigned int vicScrollMs = vicScroll(vicCon, lines);
	unsigned int vdcColPrintMs = vdcColor(vdcCon, LINE_80, lines);
	unsigned int vdcColScrollMs = vdcColorScroll(vdcCon, lines);
	unsigned int vicColPrintMs = vicColor(vicCon, LINE_40, lines);
	unsigned int vicColScrollMs = vicColorScroll(vicCon, lines);
	clearHomeCon(vicCon);
	sprintf(str, "CP/M printf         %04u ms per line", (cpmPrintMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "CP/M scroll         %04u ms per line", (cpmScrollMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VDC printCon        %04u ms per line", (vdcPrintMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VDC scrollCon       %04u ms per line", (vdcScrollMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VDC printCon color  %04u ms per line",
			(vdcColPrintMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VDC scrollCon color %04u ms per line",
			(vdcColScrollMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VIC printCon        %04u ms per line",
			((vicPrintMs * 2) / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VIC scrollCon       %04u ms per line", (vicScrollMs / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VIC printCon color  %04u ms per line",
			((vicColPrintMs * 2) / lines));
	printLineCon(vicCon, str);
	sprintf(str, "VIC scrollCon color %04u ms per line",
			(vicColScrollMs / lines));
	printLineCon(vicCon, str);
	waitKey(vicCon->scr);
}
