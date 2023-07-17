/*
 * C128 CP/M console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

#include "demo.h"

/*
 * Run console demo.
 */
void runConDemo(console *con, uchar sentences) {
	static uchar colors[] = { scrGreen, scrLightGreen, scrBlue, scrLightBlue,
	scrRed, scrLightRed, };
	uchar i;
	printWrapCon(con,
			"Here we use the console functions without color which are faster.");
	waitKey(con->scr);
	clearHomeCon(con);
	srand(inp(vicRaster));
	for (i = 0; i < sentences; i++) {
		printWrapCon(con, "This is no color output.");
		if (con->curX != 0) {
			printCon(con, " ");
		}
	}
	printLineCon(con, "");
	waitKey(con->scr);
	clearHomeCon(con);
	printWrapCon(con,
			"Here we use the console functions with color which are slower than no color.");
	waitKey(con->scr);
	clearHomeCon(con);
	/* Use color print */
	con->colorOn = 1;
	for (i = 0; i < sentences; i++) {
		con->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
		printWrapCon(con, "This is color output.");
		if (con->curX != 0) {
			printCon(con, " ");
		}
	}
	printLineCon(con, "");
	waitKey(con->scr);
}
