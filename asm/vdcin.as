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
        pop     de              ;return address
        pop     hl              ;vdc register to set
        push    hl
        push    de
        ld      a,l
        ld      bc,0d600h       ;vdc status port
        out     (c),a           ;set reg to read
1:
        in      a,(c)           ;repeat
        and     80h             ; test bit 7
        jr      z,1b            ;until bit 7 high
        inc     c               ;vdc data register
        in      l,(c)           ;get data
        ret
