/*
 * C128 CP/M console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <hitech.h>
#include <screen.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

#include "demo.h"

/*
 * Run console demo.
 */
void runConDemo(console *con, uchar sentences) {
	uchar i;
	srand(inp(vicRaster));
	for (i = 0; i < sentences; i++) {
		char *str = generateSentence();
		printWrapCon(con, str);
		free(str);
		if (con->curX != 0) {
			printCon(con, " ");
		}
	}
	printLineCon(con, "");
	waitKey(con->scr);
}
