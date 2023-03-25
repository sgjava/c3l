/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <stdlib.h>
#include <hitech.h>
#include <cia.h>
#include <vic.h>

/*
 * Key column.
 */
uchar keyCol[8] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f };

/*
 * Left shift key column.
 */
uchar lsKeyCol[8] = { 0x7e, 0x7d, 0x7b, 0x77, 0x6f, 0x5f, 0x3f, 0x7f };

/*
 * Right shift key column.
 */
uchar rsKeyCol[8] = { 0xee, 0xed, 0xeb, 0xe7, 0xdf, 0xcf, 0xaf, 0x6f };

/*
 * Key to ASCII code unshifted. Unmapped keys are set to 0x00.
 */
uchar stdKeys[11][8] = { { 0x7f, 0x0d, 0x04, 0x00, 0x00, 0x00, 0x00, 0x18 }, {
        '3', 'w', 'a', '4', 'z', 's', 'e', 0x00 }, { '5', 'r', 'd', '6', 'c',
        'f', 't', 'x' }, { '7', 'y', 'g', '8', 'b', 'h', 'u', 'v' }, { '9', 'i',
        'j', '0', 'm', 'k', 'o', 'n' },
        { '+', 'p', 'l', '-', '.', ':', '@', ',' }, { '\\', '*', ';', 0x00,
                0x00, '=', '^', '/' }, { '1', 0x00, 0x00, '2', 0x20, 0x00, 'q',
                0x00 }, { 0x00, '8', '5', 0x09, '2', '4', '7', '1' }, { 0x1b,
                '+', '-', 0x0a, 0x0d, '6', '9', '3' }, { 0x00, '0', '.', 0x05,
                0x18, 0x13, 0x04, 0x00 } };

/*
 * Key to ASCII code shifted. Unmapped keys are set to 0x00.
 */
uchar shiftKeys[11][8] = { { 0x7f, 0x0d, 0x04, 0x00, 0x00, 0x00, 0x00, 0x18 }, {
        '#', 'W', 'A', '$', 'Z', 'S', 'E', 0x00 }, { '%', 'R', 'D', '&', 'C',
        'F', 'T', 'X' }, { '\'', 'Y', 'G', '(', 'B', 'H', 'U', 'V' }, { ')',
        'I', 'J', '0', 'M', 'K', 'O', 'N' }, { '+', 'P', 'L', '-', '>', '[',
        '@', '<' }, { '\\', '*', ']', 0x00, 0x00, '=', '^', '?' }, { '!', 0x00,
        0x00, '"', 0x20, 0x00, 'Q', 0x00 }, { 0x00, '8', '5', 0x09, '2', '4',
        '7', '1' }, { 0x1b, '+', '-', 0x0a, 0x0d, '6', '9', '3' }, { 0x00, '0',
        '.', 0x05, 0x18, 0x13, 0x04, 0x00 } };

/*
 * Get key column. If column not found then 8 is returned.
 */
uchar getKeyCol(uchar keyVal) {
    register uchar i = 0;
    while ((i < 8) && (keyCol[i] != keyVal)) {
        i++;
    }
    return i;
}

/*
 * Get left shift key column. If column not found then 8 is returned.
 */
uchar getLsKeyCol(uchar keyVal) {
    register uchar i = 0;
    while ((i < 8) && (lsKeyCol[i] != keyVal)) {
        i++;
    }
    return i;
}

/*
 * Get left shift key column. If column not found then 8 is returned.
 */
uchar getRsKeyCol(uchar keyVal) {
    register uchar i = 0;
    while ((i < 8) && (rsKeyCol[i] != keyVal)) {
        i++;
    }
    return i;
}

/*
 * Get standard or extended key code for single row. 0xff is returned if no key
 * pressed. keyRow is 0 - 10.
 */
uchar getKey(uchar keyRow) {
    uchar keyCode;
    /* Standard keys? */
    if (keyRow < 8) {
        outp(vicExtKey, 0xff);
        outp(cia1DataA, keyCol[keyRow]);
        keyCode = inp(cia1DataB);
    } else {
        /* Extended keys */
        outp(cia1DataA, 0xff);
        outp(vicExtKey, keyCol[keyRow - 8]);
        keyCode = inp(cia1DataB);
    }
    return keyCode;
}

/*
 * Get all standard and extended key rows.
 */
uchar *getKeys() {
    register uchar i;
    uchar *ciaKeyScan = (uchar *) malloc(11);
    outp(vicExtKey, 0xff);
    /* Scan standard keys */
    for (i = 0; i < 8; i++) {
        outp(cia1DataA, keyCol[i]);
        ciaKeyScan[i] = inp(cia1DataB);
    }
    outp(cia1DataA, 0xff);
    /* Scan extended keys */
    for (i = 0; i < 3; i++) {
        outp(vicExtKey, keyCol[i]);
        ciaKeyScan[i + 8] = inp(cia1DataB);
    }
    return ciaKeyScan;
}

/*
 * Decode key from getKeys array. Handle shifted and unshifted keys. 0x00 is
 * returned if no keys pressed, unmapped keys pressed or unable to decode.
 */
uchar decodeKey() {
    register uchar i = 0;
    uchar keyCode = 0x00;
    uchar lsCol, rsCol, col;
    uchar *ciaKeyScan;
    ciaKeyScan = getKeys();
    /* Shift row pressed? */
    if ((ciaKeyScan[1] != 0xff) || (ciaKeyScan[6] != 0xff)) {
        lsCol = getLsKeyCol(ciaKeyScan[1]);
        rsCol = getRsKeyCol(ciaKeyScan[6]);
        /* Left shift plus key in same row? */
        if (lsCol < 7) {
            keyCode = shiftKeys[1][lsCol];
            /* Right shift plus key in same row? */
        } else if ((rsCol < 8) && (rsCol != 4)) {
            keyCode = shiftKeys[6][rsCol];
            /* Only shift pressed? */
        } else if ((ciaKeyScan[1] == 0x7f) || (ciaKeyScan[6] == 0xef)) {
            /* Find first key row */
            while ((i < 11) && (ciaKeyScan[i] == 0xff)) {
                /* Skip left shift or right shift if pressed by themselves */
                if (((i == 0) && (ciaKeyScan[1] == 0x7f))
                        || ((i == 5) && ciaKeyScan[6] == 0xef)) {
                    i++;
                }
                i++;
            }
            /* Another key pressed besides shift? */
            if (i < 11) {
                col = getKeyCol(ciaKeyScan[i]);
                /* Make sure key code is valid */
                if (col < 8) {
                    keyCode = shiftKeys[i][col];
                }
            }
            /* Row 1 not pressed? */
        } else if (ciaKeyScan[1] == 0xff) {
            col = getKeyCol(ciaKeyScan[6]);
            /* Make sure key code is valid */
            if (col < 8) {
                keyCode = stdKeys[6][col];
            }
        } else {
            /* Row 1 pressed */
            col = getKeyCol(ciaKeyScan[1]);
            /* Make sure key code is valid */
            if (col < 8) {
                keyCode = stdKeys[1][col];
            }
        }
    } else {
        /* No shift rows pressed, so find first key row */
        while ((i < 11) && (ciaKeyScan[i] == 0xff)) {
            i++;
        }
        if (i < 11) {
            col = getKeyCol(ciaKeyScan[i]);
            /* Make sure key code is valid */
            if (col < 8) {
                keyCode = stdKeys[i][col];
            }
        }
    }
    free(ciaKeyScan);
    return keyCode;
}
