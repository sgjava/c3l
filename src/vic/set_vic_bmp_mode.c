/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>

/*
 * Set bitmap mode.
 */
void setVicBmpMode(const unsigned char mmuRcr, const unsigned char vicBank, unsigned char scrLoc, unsigned char bmpLoc,
		const unsigned char mcm) {
	/*
	 * For some reason this function must be included in the app
	 * source file instead of the lib or it hangs. It works fine
	 * in text mode. Also works with HTC compiler.
	 */
	//setVicMmuBank(mmuRcr);
	setVicBank(vicBank);
	setVicMode(0, 1, mcm);
	setVicScrMem(scrLoc);
	setVicBmpMem(bmpLoc);
}
