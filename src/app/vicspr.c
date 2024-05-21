/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe sprite demo. I used Wizard of Wor sprites
 * that are composed of 4 directions and 3 sequences per
 * direction. This gives you 12 sprites total per character.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <screen.h>
#include <sid.h>
#include <stdio.h>
#include <stdlib.h>
#include <vic.h>

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024
// Protect VIC memory < 0x8000
#pragma output CRT_HEAP_ADDRESS = 0x8000

/*
 * Sprite libraries to load.
 */
#define LIB_SPRITES 5

/*
 * Sprite definitions to load.
 */
#define LOAD_SPRITES 12

/*
 * Total number of sprites loaded.
 */
#define TOTAL_SPRITES (LIB_SPRITES * LOAD_SPRITES)

/*
 * Total physical sprites.
 */
#define MAX_SPRITES 8

/*
 * Number of sprites per animation sequence.
 */
#define SEQ_SPRITES 3

/*
 * Forward reference.
 */
typedef struct sprite sprite;

/*
 * Sprite struct.
 */
typedef struct sprite {
	// Definitions array
	unsigned char *def;
	// X position
	unsigned int x;
	// Y position
	unsigned char y;
	// Default color
	unsigned char defColor;
	// Current color
	unsigned char color;
	// Update color flag
	unsigned char updateColor;
	// X direction
	int xDir;
	// Y direction
	int yDir;
	// Current sequence
	unsigned char curSeq;
	// Sequence array
	unsigned char seq[SEQ_SPRITES];
};

/*
 Load sprite into buffer.
 */
void loadSprites(unsigned char *buffer, unsigned int len, char *fileName) {
	FILE *file;
	if ((file = fopen(fileName, "rb")) != NULL) {
		printf("\nLoading %s, %u bytes to address 0x%04x", fileName, len, buffer);
		fread(buffer, sizeof(unsigned char), len, file);
		fclose(file);
	} else {
		printf("\nUnable to open file %s", fileName);
	}
}

/*
 * Load sprites, initialize key scan and screen.
 */
void init(screen *scr) {
	unsigned char i;
	unsigned int libSize = LOAD_SPRITES * 64, sprMem;
	char fileNames[LIB_SPRITES][13] = { "burwor.spr", "garwor.spr", "thorwor.spr", "worrior.spr", "wow.spr" };
	// Use ram at end of bank 1 for character set screen just above that
	initVicScr(scr, 0x7400, 0x7800);
	initVicScrMode(scr, scrBlack, scrBlue, scrWhite);
	// Calculate sprite offset by number of sprites before screen memory
	sprMem = ((unsigned int) scr->scrMem) - (libSize * LIB_SPRITES);
	// Load sprite libraries
	for (i = 0; i < LIB_SPRITES; i++) {
		loadSprites((unsigned char*) (sprMem + (i * libSize)), libSize, fileNames[i]);
	}
	// CP/M file access will enable CIA IRQ, so we init CIA after load
	initCia();
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
 * Move and animate sprites.
 */
void moveSpr(screen *scr, unsigned char *sprPtr, sprite sprites[]) {
	unsigned char i;
	/* Raster off screen? */
	while (inp(vicRaster) != 0xff)
		;
	for (i = 0; i < MAX_SPRITES; i++) {
		if (sprites[i].updateColor) {
			// Set sprite color
			outp(vicSpr0Col + i, scr->color[sprites[i].color]);
			sprites[i].updateColor = 0;
		}
		// Set sprite location
		setVicSprLoc(i, sprites[i].x, sprites[i].y);
		// Set sprite pointer
		sprPtr[i] = sprites[i].def[sprites[i].seq[sprites[i].curSeq]];
	}
}

/*
 * Collision detection.
 */
void collSpr(sprite sprites[]) {
	unsigned char i, sprCol, sprBgCol;
	static unsigned char sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	// Sprite to sprite collision register
	sprCol = inp(vicSprColl);
	// Sprite to background collision register
	sprBgCol = inp(vicSprFgColl);
	for (i = 0; i < MAX_SPRITES; i++) {
		// See if there was a sprite to sprite collision
		if (sprCol & sprTable[i]) {
			// Set sprite color
			sprites[i].color = scrRed;
			sprites[i].updateColor = 1;
			// See if there was a sprite to background collision
		} else if (sprBgCol & sprTable[i]) {
			// Set sprite color
			sprites[i].color = scrLightRed;
			sprites[i].updateColor = 1;
		} else if (sprites[i].color != sprites[i].defColor) {
			sprites[i].color = sprites[i].defColor;
			sprites[i].updateColor = 1;
		}
	}
}

/*
 * Set sprite struct members.
 */
void setSpr(sprite *spr, int xDir, int yDir, unsigned char *seq) {
	spr->xDir = xDir;
	spr->yDir = yDir;
	spr->seq[0] = seq[0];
	spr->seq[1] = seq[1];
	spr->seq[2] = seq[2];
}

/*
 * Pre-calculate movements and store in sprite struct.
 */
void calcMoveSpr(screen *scr, sprite sprites[]) {
	unsigned char i, delay = 1, *sprPtr = scr->scrMem + vicSprMemOfs;
	// Sprite sequences
	unsigned char seq[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	setSidVol(15, 0);
	// Move sprites until return pressed
	while (getKey(0) != 0xfd) {
		// Pre-calculate movements
		if (delay-- == 0) {
			for (i = 0; i < MAX_SPRITES; i++) {
				//Check X max and min
				if (sprites[i].x > 321 || rand() % 200 < 1) {
					// Left
					setSpr(&sprites[i], -1, 0, &seq[0]);
				} else if (sprites[i].x < 24 || rand() % 200 < 1) {
					// Right
					setSpr(&sprites[i], 1, 0, &seq[3]);
				} else if (sprites[i].y > 229 || rand() % 200 < 1) {
					// Up
					setSpr(&sprites[i], 0, -1, &seq[6]);
				} else if (sprites[i].y < 51 || rand() % 200 < 1) {
					// Down
					setSpr(&sprites[i], 0, 1, &seq[9]);
				}
				sprites[i].curSeq += 1;
				// Check current sequence
				if (sprites[i].curSeq == SEQ_SPRITES) {
					sprites[i].curSeq = 0;
				}
				// Calc sprite x,y based on dir
				sprites[i].x += sprites[i].xDir;
				sprites[i].y += sprites[i].yDir;
			}
			// Collision detection
			collSpr(sprites);
			// Move all sprites
			moveSpr(scr, sprPtr, sprites);
			// How many vblank cycles to wait
			delay = 5;
		} else {
			/* Raster off screen? */
			while (inp(vicRaster) != 0xff)
				;
		}
	}
	// Disable all sprites
	for (i = 0; i < MAX_SPRITES; i++) {
		disableVicSpr(i);
	}
	clearSid();
}

/*
 * Initialize sprite pointers and struct array.
 */
void initSpr(screen *scr, unsigned char sprDef[], sprite sprites[]) {
	unsigned char i, vicBank = (unsigned int) scr->scrMem / 16384, *sprPtr = scr->scrMem + vicSprMemOfs;
	unsigned char def, seq[] = { 0, 1, 2 };
	unsigned char sprColor[5] = { scrCyan, scrYellow, scrGreen, scrPurple, scrLightBlue };
	// Seed random number generator with VIC raster value
	srand(inp(vicRaster));
	// Configure all sprite definition offsets
	for (i = 0; i < TOTAL_SPRITES; i++) {
		sprDef[i] = (((unsigned int) scr->scrMem) - (vicBank * 16384) - ((i + 1) * 64)) / 64;
	}
	// Configure all sprites
	for (i = 0; i < MAX_SPRITES; ++i) {
		// Configure sprite
		def = rand() % 5;
		sprites[i].def = &sprDef[def * 12];
		sprites[i].defColor = sprColor[def];
		sprites[i].curSeq = rand() % 3;
		sprites[i].x = (i * 26) + 24;
		sprites[i].y = 200;
		sprites[i].color = sprites[i].defColor;
		sprites[i].updateColor = 0;
		setSpr(&sprites[i], -1, 0, &seq[0]);
		// Set sprite pointer
		sprPtr[i] = sprDef[sprites[i].seq[sprites[i].curSeq]];
		// Set sprite location
		setVicSprLoc(i, sprites[i].x, sprites[i].y);
		// Set sprite color
		outp(vicSpr0Col + i, scr->color[sprites[i].color]);
		// Enable sprite
		enableVicSpr(i);
	}
}

/*
 * Run demo.
 */
void run(screen *scr) {
	unsigned char i;
	char str[41];
	unsigned char sprDef[TOTAL_SPRITES];
	sprite sprites[MAX_SPRITES];
	(scr->print)(scr, 0, 0, "Using RAM character set and one screen  "
			"at the end of VIC bank 1. Sprites are   "
			"located above screen. Collision         "
			"detection changes color.");
	sprintf(str, "chr:    %04x", scr->chrMem);
	(scr->printCol)(scr, 0, 5, scrLightGreen, str);
	sprintf(str, "scr:    %04x", scr->scrMem);
	(scr->printCol)(scr, 0, 6, scrLightGreen, str);
	// Use VIC raster to seed random numbers
	srand(inp(vicRaster));
	initSpr(scr, sprDef, sprites);
	calcMoveSpr(scr, sprites);
}

main() {
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	init(scr);
	run(scr);
	done();
	/* Free memory */
	free(scr);
}
