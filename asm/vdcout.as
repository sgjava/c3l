;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set VDC register
;

global  _outVdc
psect   text

_outVdc:
        pop     hl              ;return address
        pop     bc              ;vdc register to write
        pop     de              ;data
        push    de
        push    bc
        push    hl
        ld      a,c
        ld      bc,0d600h       ;vdc status port
        out     (c),a           ;set reg to read
1:
        in      a,(c)           ;repeat
        and     80h             ;  test bit 7
        jr      z,1b            ;until bit 7 high
        inc     c               ;vdc data register
        out     (c),e           ;set data
        ret
       