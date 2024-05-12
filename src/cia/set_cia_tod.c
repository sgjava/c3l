/*
 * C128 6526 CIA functions.
 *
 * Set CIA TOD clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 Set CIA 2 TOD clock.
 */
void setCiaTod(unsigned int cia, unsigned char hour, unsigned char min,
		unsigned char sec, unsigned char tenth) {
	// CIA TOD hour
	outp(cia+ciaTodHrs, hour);
	// CIA TOD minute
	outp(cia+ciaTodMin, min);
	// CIA TOD second
	outp(cia+ciaTodSec, sec);
	// CIA TOD tenth second (this starts timer)
	outp(cia+ciaTodTen, tenth);
}
