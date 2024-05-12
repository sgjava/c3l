/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>

/*
 * Set bitmap mode.
 */
void setVicBmpMode(unsigned char mmuRcr, unsigned char vicBank,
		unsigned char scrLoc, unsigned char bmpLoc) {
	/*
	 * For some reason this function must be included in the app
	 * source file instead of the lib or it hangs. It works fine
	 * in text mode. Also works with HTC compiler.
	 */
	//setVicMmuBank(mmuRcr);
	setVicBank(vicBank);
	setVicMode(0, 1, 0);
	setVicScrMem(scrLoc);
	setVicBmpMem(bmpLoc);
}
