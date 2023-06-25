/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <sys.h>
#include <vic.h>

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void doneVic() {
	restoreVic();
	/* CPM default */
	setVicMmuBank(0);
	setVicBank(0);
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
}
