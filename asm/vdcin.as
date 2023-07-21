;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Get VDC register
;

global  _inVdc
psect   text

_inVdc:
        pop     de              ; Return address
        pop     hl              ; VDC register to set
        push    hl
        push    de
        ld      a,l
        ld      bc,0d600h       ; VDC status port
        out     (c),a           ; Set reg to read
1:
        in      a,(c)           ; Repeat
        and     80h             ;   Test bit 7
        jr      z,1b            ; Until bit 7 high
        inc     c               ; VDC data register
        in      l,(c)           ; Get data
        ret
