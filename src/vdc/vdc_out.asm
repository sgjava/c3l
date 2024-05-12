;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set VDC register
;

SECTION code_clib
PUBLIC  outVdc
PUBLIC  _outVdc

outVdc:
_outVdc:
        pop     hl              ; Return address?
        pop     de              ; Data
        pop     bc              ; VDC register to write
        push    bc
        push    de
        push    hl
        ld      a,c
        ld      bc,0d600h       ; VDC status port
        out     (c),a           ; Set reg to read
rep1:
        in      a,(c)           ; Repeat
        and     80h             ;   Test bit 7
        jr      z,rep1          ; Until bit 7 high
        inc     c               ; VDC data register
        out     (c),e           ; Set data
        ret
