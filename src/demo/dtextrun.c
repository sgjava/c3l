/*
 * C128 CP/M real time key press decode.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <hitech.h>
#include <screen.h>
#include <stdio.h>
#include <sys.h>

/*
 * Get elapsed time from CIA 2.
 */
ushort elapsedMs() {
	return 0xffff - (inp(cia2+ciaTimerBHi) * 256 + inp(cia2+ciaTimerBLo));
}

/*
 * CP/M print speed.
 */
ushort cpmPrint(char *str, ushort lines) {
	ushort i;
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printf(str);
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * CP/M print speed.
 */
ushort cpmScroll(ushort lines) {
	ushort i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printf("\n");
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VDC print speed.
 */
ushort vdcPrint(console *con, char *str, ushort lines) {
	ushort i;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VDC scroll speed.
 */
ushort vdcScroll(console *con, ushort lines) {
	ushort i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VIC print speed.
 */
ushort vicPrint(console *con, char *str, ushort lines) {
	ushort i;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VIC scroll speed.
 */
ushort vicScroll(console *con, ushort lines) {
	ushort i;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	return elapsedMs();
}

/*
 * VDC color print speed.
 */
ushort vdcColor(console *con, char *str, ushort lines) {
	ushort i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * VDC color scroll speed.
 */
ushort vdcColorScroll(console *con, ushort lines) {
	ushort i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * VIC color print speed.
 */
ushort vicColor(console *con, char *str, ushort lines) {
	ushort i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	clearHomeCon(con);
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printCon(con, str);
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * VIC color scroll speed.
 */
ushort vicColorScroll(console *con, ushort lines) {
	ushort i;
	con->colorOn = 1;
	con->color = scrLightGreen;
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < lines; i++) {
		printLineCon(con, "");
	}
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	con->colorOn = 0;
	return elapsedMs();
}

/*
 * Run demo.
 */
void runTextDemo(console *vicCon, console *vdcCon, ushort cpmPrintMs,
		ushort cpmScrollMs, ushort lines) {
	static char *LINE_80 =
			"01234567890123456789012345678901234567890123456789012345678901234567890123456789";
	static char *LINE_40 = "0123456789012345678901234567890123456789";
	char str[41];
	ushort vdcPrintMs = vdcPrint(vdcCon, LINE_80, lines);
	ushort vdcScrollMs = vdcScroll(vdcCon, lines);
	ushort vicPrintMs = vicPrint(vicCon, LINE_40, lines);
	ushort vicScrollMs = vicScroll(vicCon, lines);
	ushort vdcColPrintMs = vdcColor(vdcCon, LINE_80, lines);
	ushort vdcColScrollMs = vdcColorScroll(vdcCon, lines);
	ushort vicColPrintMs = vicColor(vicCon, LINE_40, lines);
	ushort vicColScrollMs = vicColorScroll(vicCon, lines);
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
