/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe sprite demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <cia.h>
#include <vic.h>
#include <sid.h>
#include "hitech.h"
#include "sys.h"

/*
 * Sprite data.
 */
uchar sprData[] = { 0x00, 0x7e, 0x00, 0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x1f,
		0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x3f, 0xff, 0xfc, 0x7f, 0xff, 0xfe, 0x7f,
		0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x3f,
		0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x07, 0xff, 0xe0, 0x03,
		0xff, 0xc0, 0x00, 0x7e, 0x00 };

/*
 * Configure CIA to kill interrupts and enable keyboard scan.
 */
void initCia() {
	/* ~1 millisecond */
	int timerA = 992;
	int timerB = 0xffff;
	/* Clear all CIA 1 IRQ enable bits */
	outp(cia1Icr, ciaClearIcr);
	/* Clear CIA 1 ICR status */
	inp(cia1Icr);
	/* Clear all CIA 2 IRQ enable bits */
	outp(cia2Icr, ciaClearIcr);
	/* Clear CIA 2 ICR status */
	inp(cia2Icr);
	/* CIA 2 Timer A lo */
	outp(cia2TimerALo, (uchar) timerA);
	/* CIA 2 Timer A hi */
	outp(cia2TimerAHi, (uchar) (timerA >> 8));
	/* CIA 2 Timer B lo */
	outp(cia2TimerBLo, (uchar) timerB);
	/* CIA 2 Timer B hi */
	outp(cia2TimerBHi, (uchar) (timerB >> 8));
	/* Link time to count and enable timer */
	outp(cia2CtrlRegB, ciaCountA);
	/* Set CIA 1 DDRs for keyboard scan */
	outp(cia1DdrA, 0xff);
	outp(cia1DdrB, 0x00);
}

/*
 * Initialize key scan and screen.
 */
void init(screen *scr) {
	uchar vicBank;
	initCia();
	clearSid();
	/* VIC Screen configuration */
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	/* Use ROM character set */
	scr->chrMem = (uchar*) 0x1800;
	/* Use ram at end of bank 0 */
	scr->scrMem = (uchar*) 0x3c00;
	scr->scrColMem = (uchar*) vicColMem;
	scr->clearScr = clearVicScr;
	scr->clearScrCol = clearVicCol;
	scr->print = printVicPet;
	scr->printCol = printVicColPet;
	/* Black screen and border */
	outp(vicBorderCol, vicBlack);
	outp(vicBgCol0, vicBlack);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Set standard character mode using MMU bank 1 and set VIC based on scr location */
	vicBank = (ushort) scr->scrMem / 16384;
	setVicChrMode(1, vicBank, ((ushort) scr->scrMem - (vicBank * 16384)) / 1024,
			((ushort) scr->chrMem - (vicBank * 16384)) / 2048);
	/* Clear color to white */
	(scr->clearScrCol)(scr, vicWhite);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(screen *scr, uchar bgCol, uchar fgCol) {
	clearSid();
	/* Restore screen/border colors */
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, ciaEnableIrq);
}

/*
 * Wait for Return key to be pressed.
 */
void waitKey(screen *scr) {
	(scr->printCol)(scr, 0, 24, 7, "Press Return");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
}

/*
 * Sound effect.
 */
void sound() {
	setSidEnv(sidVoice1, 0, 0, 15, 9);
	setSidFreq(sidVoice1, 200);
	setSidAtt(sidVoice1, sidNoi);
	setSidRel(sidVoice1, sidNoi);
}

/*
 * Bounce sprite around screen.
 */
void bounceSpr(screen *scr) {
	char str[40];
	int moves = 0;
	int timerB = 0xffff;
	int timerVal;
	uchar y = 50, inFront = 0, color = 6, i;
	ushort x = 24;
	int xDir = 1, yDir = 1;
	uchar *spr = (uchar*) ((ushort) scr->scrMem) - 64;
	/* Store sprite data in VIC memory above screen */
	for (i = 0; i < 63; i++) {
		spr[i] = sprData[i];
	}
	configVicSpr(scr, spr, 0, 6);
	setVicSprLoc(0, x, y);
	enableVicSpr(0);
	(scr->printCol)(scr, 0, 24, 7, "Press Return");
	setSidVol(15, 0);
	outp(cia2CtrlRegA, ciaCpuCont);
	/* Bounce sprite until return pressed */
	while (getKey(0) != 0xfd) {
		x += xDir;
		y += yDir;
		if (x > 321) {
			x = 321;
			xDir = -1;
			sound();
		} else if (x < 24) {
			x = 24;
			xDir = 1;
			sound();
		} else if (y > 230) {
			y = 228;
			yDir = -1;
			sound();
		} else if (y < 50) {
			y = 50;
			yDir = 1;
			sound();
		}
		/* Raster off screen? */
		 while ((inp(vicCtrlReg1) & 0x80) != 0x80)
		 ;
		/* Move sprite */
		setVicSprLoc(0, x, y);
		/* Did sprite collide with text? */
		if ((inp(vicSprFgColl) & 0x01) == 0x01) {
			if (color == 6) {
				color = 2;
				outp(vicSpr0Col, color);
			}
		} else {
			if (color == 2) {
				color = 6;
				outp(vicSpr0Col, color);
			}
		}
		/* Toggle sprite FG/BG mode */
		if (rand() > 32700) {
			if (inFront) {
				inFront = 0;
				setVicSprFg(0);
			} else {
				inFront = 1;
				setVicSprBg(0);
			}
		}
		moves++;
	}
	outp(cia2CtrlRegA, ciaStopTimer);
	timerVal = timerB - (inp(cia2TimerBHi) * 256 + inp(cia2TimerBLo));
	sprintf(str, "Each movement %d ms", timerVal / moves);
	(scr->printCol)(scr, 0, 19, 1, str);
	disableVicSpr(0);
	clearSid();
	waitKey(scr);
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	uchar i;
	char str[40];
	/* Note the use of printVicPet that converts ASCII to PETSCII */
	(scr->print)(scr, 0, 0, "Using ROM character set and one screen  "
			"at the end of VIC bank 0. Sprite is     "
			"located above screen at 0x3bc0.         "
			"Collision detection changes color.");
	for (i = 0; i < 255; i++) {
		scr->scrMem[i + 280] = i;
	}
	sprintf(str, "mem:    %04x", vicMem);
	(scr->printCol)(scr, 0, 15, 14, str);
	sprintf(str, "chr:    %04x", scr->chrMem);
	(scr->printCol)(scr, 0, 16, 14, str);
	sprintf(str, "scr:    %04x", scr->scrMem);
	(scr->printCol)(scr, 0, 17, 14, str);
	/* Use VIC raster to seed random numbers */
	srand(inp(vicRaster));
	bounceSpr(scr);
}

main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Save screen/border color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(scr, border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
}
