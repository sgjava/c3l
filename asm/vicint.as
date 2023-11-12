;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Interrupt code to be called by 0xfdfd vector. Do not call this function directly.
;

global  _vicInt

psect   data

save_sp:

defw    0

stack:

defs    16

stack_end:                     ; End of stack

psect   text

_vicInt:
        ld      (save_sp),sp    ; Save SP
        ld      sp,stack_end
        push    af
        push    bc
        ld      bc,0dc0dh
        in      a,(c)           ; Clear CIA 1 ICR status        
        ld      bc,0d020h       ; VIC border color
        in      a,(c)           ; Get current color              
        inc     a
        out     (c),a           ; Set new color
	    pop     bc
	    pop     af
	    done:
	    ld      sp,(save_sp)    ; Restore SP
        ei
        ret
       