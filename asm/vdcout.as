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
        pop     hl              ; Return address
        pop     bc              ; VDC register to write
        pop     de              ; Data
        push    de
        push    bc
        push    hl
        ld      a,c
        ld      bc,0d600h       ; VDC status port
        out     (c),a           ; Set reg to read
1:
        in      a,(c)           ; Repeat
        and     80h             ;   Test bit 7
        jr      z,1b            ; Until bit 7 high
        inc     c               ; VDC data register
        out     (c),e           ; Set data
        ret
       