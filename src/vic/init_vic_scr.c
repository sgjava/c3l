/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>

/*
 * Initialize screen struct for VIC.
 */
void initVicScr(const screen *scr, const unsigned int scrMem, const unsigned int chrMem) {
	static unsigned char vicColors[16] = { vicBlack, vicWhite, vicRed, vicCyan,
	vicPurple, vicGreen, vicBlue, vicYellow, vicOrange, vicBrown, vicLightRed,
	vicDarkGray, vicMedGray, vicLightGreen, vicLightBlue, vicLightGray };
	/* Map colors */
	unsigned char i, len = sizeof(vicColors);
	for (i = 0; i < len; i++) {
		scr->color[i] = vicColors[i];
	}
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	scr->chrMem = (unsigned char*) chrMem;
	scr->scrMem = (unsigned char*) scrMem;
	scr->scrColMem = (unsigned char*) vicColMem;
	scr->clearScr = clearVicScr;
	scr->clearScrCol = clearVicCol;
	/* Assign print functions based on character set address */
	if (chrMem == 0x1000 || chrMem == 0x1800 || chrMem == 0x9000
			|| chrMem == 0x9800) {
		/* ROM */
		scr->print = printVicPet;
		scr->printCol = printVicColPet;
	} else {
		/* RAM */
		scr->print = printVic;
		scr->printCol = printVicCol;
	}
	scr->scrollUp = scrollVicUp;
	scr->scrollUpCol = scrollVicUpCol;
	scr->fillMem = fillVicMem;
	scr->copyScrToStr = copyVicToStr;
}
