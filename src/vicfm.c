/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "hitech.h"

/*
 * Fill memory with word value.
 */
void fillVicMem(uchar *mem, ushort len, ushort value) {
    register ushort i;
    ushort *mem16 = (ushort *) mem;
    for (i = 0; i < len; i++) {
        mem16[i] = value;
    }
}
