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
void dualRandSentence(console *vicCon, console *vdcCon, uchar sentences, uchar color) {
	static uchar colors[] = { scrGreen, scrLightGreen, scrBlue, scrLightBlue,
	scrRed, scrLightRed};
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
			vicCon->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
			vdcCon->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
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
 * Run demo.
 */
void runDualDemo(console *vicCon, console *vdcCon) {
	dualRandSentence(vicCon, vdcCon, 100, 0);
	dualRandSentence(vicCon, vdcCon, 100, 1);
	waitKey(vicCon->scr);
}
