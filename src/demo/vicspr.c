/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe sprite demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <screen.h>
#include <sid.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

/*
 * Initialize key scan and screen.
 */
void init(screen *scr) {
	initCia();
	/* Use ram at end of bank 0 */
	initVicScr(scr, 0x3c00, 0x1800);
	initVicScrMode(scr, scrBlack, scrBlack, scrWhite);
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done() {
	clearSid();
	doneVic();
	doneCia();
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
 * Configure sprite.
 */
void configSpr(screen *scr, ushort x, uchar y) {
	static uchar sprData[] = { 0x00, 0x00, 0x18, 0x01, 0xfc, 0x30, 0x03, 0x38,
			0x78, 0x1e, 0xbc, 0x78, 0x1f, 0xf8, 0x38, 0x0a, 0xfc, 0x70, 0x1f,
			0xf8, 0x60, 0x0f, 0x3c, 0xc0, 0x00, 0x38, 0x80, 0x00, 0x3d, 0x00,
			0x07, 0xff, 0x80, 0x0f, 0xff, 0xc0, 0x07, 0x3f, 0xe0, 0x03, 0x01,
			0xe0, 0x01, 0x80, 0xc0, 0x0f, 0xc0, 0xc0, 0x00, 0x01, 0xe0, 0x00,
			0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00 };
	uchar i, *spr = (uchar*) ((ushort) scr->scrMem) - 64;
	/* Store sprite data in VIC memory above screen */
	for (i = 0; i < 63; i++) {
		spr[i] = sprData[i];
	}
	configVicSpr(scr, spr, 0, scr->color[scrGreen]);
	setVicSprLoc(0, x, y);
	enableVicSpr(0);
}

/*
 * Bounce sprite around screen.
 */
void bounceSpr(screen *scr) {
	uchar y = 50, inFront = 0, color = scr->color[scrGreen];
	ushort x = 24;
	int xDir = 1, yDir = 1;
	configSpr(scr, x, y);
	(scr->printCol)(scr, 0, scr->scrHeight - 1, scrYellow, "Press Return");
	setSidVol(15, 0);
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
			if (color == scr->color[scrGreen]) {
				color = scr->color[scrRed];
				outp(vicSpr0Col, color);
			}
		} else {
			if (color == scr->color[scrRed]) {
				color = scr->color[scrGreen];
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
	}
	disableVicSpr(0);
	clearSid();
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	uchar i;
	char str[41];
	/* Note the use of printVicPet that converts ASCII to PETSCII */
	(scr->print)(scr, 0, 0, "Using ROM character set and one screen  "
			"at the end of VIC bank 0. Sprite is     "
			"located above screen at 0x3bc0.         "
			"Collision detection changes color.");
	for (i = 0; i < 255; i++) {
		scr->scrMem[i + 280] = i;
	}
	sprintf(str, "mem:    %04x", vicMem);
	(scr->printCol)(scr, 0, 15, scrLightBlue, str);
	sprintf(str, "chr:    %04x", scr->chrMem);
	(scr->printCol)(scr, 0, 16, scrLightBlue, str);
	sprintf(str, "scr:    %04x", scr->scrMem);
	(scr->printCol)(scr, 0, 17, scrLightBlue, str);
	/* Use VIC raster to seed random numbers */
	srand(inp(vicRaster));
	bounceSpr(scr);
}

main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	init(scr);
	run(scr, vicMem);
	done();
	/* Free memory */
	free(vicMem);
	free(scr);
}
