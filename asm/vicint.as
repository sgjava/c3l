;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Interrupt code to be called by 0xfdfd vector. Do not call this function directly.
;
; See https://github.com/csoren/c128cpm/blob/bf6a9c4498afe5ef50dce6ee124b65a02b75c117/cpm/cxintr.asm
;

global  _vicInt

psect   text

_vicInt:
        push    af              ; Only pushing 4 bytes on the stack, so no creating new SP
        push    bc
        ld      bc,0dc0dh
        in      a,(c)           ; Clear CIA 1 ICR status        
        ld      bc,0d020h       ; VIC border color
        in      a,(c)           ; Get current color              
        inc     a               ; Add one
        out     (c),a           ; Set new color
	    pop     bc
	    pop     af
        ei
        ret
       