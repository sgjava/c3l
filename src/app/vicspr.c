/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe sprite demo. I used Wizard of Wor sprites that are composed of 4 directions and 3 sequences per direction.
 * This gives you 12 sprites total per character. Collisions are detected between sprites and characters. Sprite to sprite collisions
 * also queue a stateful sound engine (up to 3 sounds at one time).
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
 * Number of voices.
 */
#define SID_VOICES 3

/*
 * SID state while playing sound.
 */
#define SID_INIT 0
#define SID_SUSTAIN 1
#define SID_RELEASE 2
#define SID_DONE 3

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
 * Forward reference.
 */
typedef struct sound sound;

/*
 * SID sound.
 */
typedef struct sound {
	unsigned int voice;
	unsigned char attack;
	unsigned char decay;
	unsigned char sustain;
	unsigned char release;
	unsigned int freq;
	// Attack and release waveform
	unsigned char waveform;
	// If called 1/60 of a second is 16.66 ms
	unsigned int sustainDelay;
	// If called 1/60 of a second is 16.66 ms
	unsigned int releaseDelay;
	// SID state in life cycle
	unsigned char state;
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
 * Stateful sound effect. Called ~ 1/60 a second for NTSC.
 */
void playSound(sound s[]) {
	unsigned char i;
	// Cycle through all 3 voices
	for (i = 0; i < SID_VOICES; ++i) {
		// Check state
		switch (s[i].state) {
		case SID_INIT:
			// Start ADS
			setSidEnv(s[i].voice, s[i].attack, s[i].decay, s[i].sustain, s[i].release);
			setSidFreq(s[i].voice, s[i].freq);
			setSidAtt(s[i].voice, s[i].waveform);
			s[i].state = SID_SUSTAIN;
			break;
		case SID_SUSTAIN:
			// Sustain based on delay value
			if (!s[i].sustainDelay--) {
				// Start release
				setSidRel(s[i].voice, s[i].waveform);
				s[i].state = SID_RELEASE;
			}
			break;
		case SID_RELEASE:
			// Release delay
			if (!s[i].releaseDelay--) {
				// End release and silence voice
				setSidFreq(s[i].voice, 0);
				s[i].state = SID_DONE;
			}
			break;
		default:
			s[i].state = SID_DONE;
		}
	}
}

/*
 * Set sound effect.
 */
void setSound(sound s[]) {
	unsigned char i = 0;
	static unsigned int voice[] = { sidVoice1, sidVoice2, sidVoice3 };
	// Find free voice
	while (i < SID_VOICES && s[i].state != SID_DONE) {
		i++;
	}
	// If there's a free voice, use it
	if (i < SID_VOICES) {
		s[i].state = SID_INIT;
		s[i].voice = voice[i];
		s[i].attack = 0;
		s[i].decay = 0;
		s[i].sustain = 15;
		s[i].release = 11;
		s[i].freq = 200;
		s[i].waveform = sidNoi;
		s[i].sustainDelay = 1;
		s[i].releaseDelay = 150;
	}
}

/*
 * Collision detection and sound effect.
 */
void collSpr(sprite sprites[], sound sounds[]) {
	unsigned char i, sprCol, sprBgCol, coll;
	static unsigned char sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	// Sprite to sprite collision register
	sprCol = inp(vicSprColl);
	// Sprite to background collision register
	sprBgCol = inp(vicSprFgColl);
	coll = 0;
	for (i = 0; i < MAX_SPRITES; i++) {
		// See if there was a sprite to sprite collision
		if (sprCol & sprTable[i]) {
			// Set sprite color if not already set
			if (sprites[i].color == sprites[i].defColor) {
				sprites[i].color = scrRed;
				sprites[i].updateColor = 1;
				// Set sound one once per iteration
				if (!coll) {
					setSound(sounds);
					coll = 1;
				}
			}
			// See if there was a sprite to background collision
		} else if (sprBgCol & sprTable[i]) {
			// Set sprite color if not already set
			if (sprites[i].color == sprites[i].defColor) {
				sprites[i].color = scrLightRed;
				sprites[i].updateColor = 1;
			}
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
void calcMoveSpr(screen *scr, sprite sprites[], sound sounds[]) {
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
			collSpr(sprites, sounds);
			// Move all sprites
			moveSpr(scr, sprPtr, sprites);
			// How many vblank cycles to wait
			delay = 4;
			playSound(sounds);
		} else {
			playSound(sounds);
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
 * Initialize sound.
 */
void initSound(sound sounds[]) {
	unsigned char i;
	for (i = 0; i < SID_VOICES; ++i) {
		sounds[i].state = SID_DONE;
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
	sound sounds[SID_VOICES];
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
	initSound(sounds);
	initSpr(scr, sprDef, sprites);
	calcMoveSpr(scr, sprites, sounds);
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
