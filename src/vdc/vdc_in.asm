;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Get VDC register
;

SECTION code_clib
PUBLIC  inVdc
PUBLIC  _inVdc

; __z88dk_fastcall used in header

inVdc:
_inVdc:
        ld      a,l
        ld      bc,0d600h       ; VDC status port
        out     (c),a           ; Set reg to read
rep1:
        in      a,(c)           ; Repeat
        and     80h             ;   Test bit 7
        jr      z,rep1          ; Until bit 7 high
        inc     c               ; VDC data register
        in      l,(c)           ; Get data
        ld      h, 0            ; Set high byte to 0
        ret
