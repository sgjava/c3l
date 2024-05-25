/*
 * C128 CP/M C Library C3L
 *
 * C128 6581/8580 SID demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 *
 */

#pragma output noprotectmsdos

#include <cia.h>
#include <sid.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * MS delay up to 65535.
 */
void delay(const unsigned int ms) {
	/* Timer A counts milliseconds */
	startTimerAB(cia2, ciaMs, ms, ciaCountA);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	/* Wait for ICR flag */
	while ((inp(cia2+ciaIcr) & 0x02) == 0)
		;
}

/*
 * Plane sound.
 */
void planeSound() {
	unsigned int pulse;
	unsigned int freq = 2047;
	setSidVol(15, 0);
	setSidEnv(sidVoice1, 12, 10, 0, 0);
	setSidAtt(sidVoice1, sidSqu);
	for (pulse = 0; pulse < 3840; pulse += 10) {
		setSidPulWav(sidVoice1, pulse);
		setSidFreq(sidVoice1, freq);
		freq -= 5;
		delay(2);
	}
	setSidRel(sidVoice1, sidSqu);
	delay(6);
	setSidFreq(sidVoice1, 0);
}

/*
 * Tommy gun sound.
 */
void tommyGunSound() {
	unsigned char i;
	setSidVol(15, 0);
	for (i = 0; i < 20; i++) {
		setSidEnv(sidVoice1, 0, 3, 0, 0);
		setSidFreq(sidVoice1, 5360);
		setSidAtt(sidVoice1, sidNoi);
		delay(100);
		setSidRel(sidVoice1, sidNoi);
		delay(6);
	}
	setSidFreq(sidVoice1, 0);
}

/*
 * Explode sound.
 */
void explodeSound() {
	setSidVol(15, 0);
	setSidEnv(sidVoice1, 0, 0, 15, 11);
	setSidFreq(sidVoice1, 200);
	setSidAtt(sidVoice1, sidNoi);
	delay(8);
	setSidRel(sidVoice1, sidNoi);
	delay(2400);
	setSidFreq(sidVoice1, 0);
}

/*
 * Bomb drop sound.
 */
void bombDropSound() {
	unsigned short i;
	setSidVol(15, 0);
	setSidEnv(sidVoice3, 13, 0, 15, 0);
	setSidFreq(sidVoice3, 0);
	setSidAtt(sidVoice3, sidTri);
	for (i = 32000; i > 200; i -= 200) {
		setSidFreq(sidVoice3, i);
		delay(18);
	}
	setSidRel(sidVoice3, sidTri);
	delay(6);
	setSidFreq(sidVoice3, 0);
}

main() {
	initCia();
	printf("\nPlane\n");
	planeSound();
	printf("Tommy gun\n");
	tommyGunSound();
	printf("Bomb drop\n");
	bombDropSound();
	printf("Explode\n");
	explodeSound();
	setSidVol(0, 0);
	doneCia();
}
