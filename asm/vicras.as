;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Interrupt code to be called by 0xfdfd vector. Do not call this function directly.
;

global  _vicRas

psect   data

psect   text

_vicRas:
        push    af              ; Only pushing 4 bytes on the stack, so no creating new SP
        push    bc
        ld      bc,0d020h       ; VIC border color
        in      a,(c)           ; Get current color              
        inc     a               ; Add one
        out     (c),a           ; Set new color        
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt        
	    pop     bc
	    pop     af
        ei
        ret
       