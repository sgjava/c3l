/*
 * C128 CP/M console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <sys.h>
#include <vic.h>

#include "demo.h"

/*
 * Generate random sentences on both VIC and VDC,
 */
void dualRandSentence(console *vicCon, console *vdcCon, uchar sentences,
uchar color) {
	static uchar colors[] = { scrGreen, scrLightGreen, scrBlue, scrLightBlue,
	scrRed, scrLightRed };
	uchar i;
	char *str;
	if (color) {
		vicCon->colorOn = 1;
		vdcCon->colorOn = 1;
	} else {
		vicCon->colorOn = 0;
		vdcCon->colorOn = 0;
	}
	srand(inp(vicRaster));
	for (i = 0; i < sentences; i++) {
		if (color) {
			vicCon->color =
					colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
			vdcCon->color =
					colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
		}
		str = generateSentence();
		printWrapCon(vicCon, str);
		free(str);
		if (vicCon->curX != 0) {
			printCon(vicCon, " ");
		}
		str = generateSentence();
		printWrapCon(vdcCon, str);
		free(str);
		if (vdcCon->curX != 0) {
			printCon(vdcCon, " ");
		}
	}
	printLineCon(vicCon, "");
	printLineCon(vdcCon, "");
}

/*
 * Display color mappings VIC and VDC,
 */
void dualColors(console *vicCon, console *vdcCon) {
	static char *colorNames[16][1] = { { "scrBlack" }, { "scrWhite" }, { "scrRed" }, {
			"scrCyan" }, { "scrPurple" }, { "scrGreen" }, { "scrBlue" }, {
			"scrYellow" }, { "scrOrange" }, { "scrBrown" }, { "scrLightRed" }, {
			"scrDarkGray" }, { "scrMedGray" }, { "scrLightGreen" }, {
			"scrLightBlue" }, { "scrLightGray" }};
	uchar i;
	vicCon->colorOn = 1;
	vdcCon->colorOn = 1;
	for (i = 0; i < 16; i++) {
		vicCon->color = i;
		printLineCon(vicCon, colorNames[i][0]);
		vdcCon->color = i;
		printLineCon(vdcCon, colorNames[i][0]);
	}
}

/*
 * Run demo.
 */
void runDualDemo(console *vicCon, console *vdcCon) {
	dualRandSentence(vicCon, vdcCon, 100, 0);
	dualRandSentence(vicCon, vdcCon, 100, 1);
	waitKey(vicCon->scr);
	clearHomeCon(vicCon);
	clearHomeCon(vdcCon);
	dualColors(vicCon, vdcCon);
	waitKey(vicCon->scr);
}
