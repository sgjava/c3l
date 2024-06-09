/*
 * C128 CP/M console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <demo.h>
#include <screen.h>
#include <stdlib.h>
#include <vic.h>

void randSentence(const console *con, const unsigned char sentences, const unsigned char color) {
	static unsigned char colors[] = { scrGreen, scrLightGreen, scrBlue, scrLightBlue,
	scrRed, scrLightRed };
	unsigned char i;
	char *str;
	if (color) {
		printWrapCon(con, "Here we use the console functions with color which are slower than no color.");
		con->colorOn = 1;
	} else {
		printWrapCon(con, "Here we use the console functions without color which are faster.");
		con->colorOn = 0;
	}
	waitKey(con->scr);
	clearHomeCon(con);
	srand(inp(vicRaster));
	for (i = 0; i < sentences; i++) {
		if (color) {
			con->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
		}
		str = generateSentence();
		printWrapCon(con, str);
		free(str);
		if (con->curX != 0) {
			printCon(con, " ");
		}
	}
	printLineCon(con, "");
	waitKey(con->scr);
	clearHomeCon(con);
}

/*
 * Run console demo.
 */
void runConDemo(const console *con, const unsigned char sentences) {
	randSentence(con, sentences, 0);
	randSentence(con, sentences, 1);
}
