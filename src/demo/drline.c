/*
 * C128 CP/M simple line editor using console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <screen.h>
#include <stdlib.h>

/*
 * Simple screen line editor.
 */
void readLine(console *con) {
	screen *scr = con->scr;
	char *str;
	clearHomeCon(con);
	printLineCon(con, "Type in line and press return:");
	printLineCon(con, "");
	str = readLineCon(con, 255);
	printLineCon(con, "");
	printLineCon(con, "");
	printLineCon(con, "You entered:");
	printLineCon(con, "");
	printCon(con, str);
	free(str);
	waitKey(scr);
}
