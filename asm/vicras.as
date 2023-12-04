;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Interrupt code to be called by 0xfdfd vector. Do not call this function directly.
;

global  _vicRas

psect   data

; Save current border color

border:

defb    0

psect   text

_vicRas:
        push    af              ; Only pushing 4 bytes on the stack, so no creating new SP
        push    bc
        ld      bc,0d012h       ; VIC raster line
        in      a,(c)           ; Get current line
        cp      151             ; This is the start line
        jp      nz, 1f          ; Not 034h then jump
        ld      a, 159          ; Next raster line
        out     (c),a           ; Set line to fire IRQ on        
        ld      bc,0d020h       ; VIC border color
        in      a,(c)           ; Get current color
        ld      (border),a      ; Save border color    
        inc     a               ; Add one
        out     (c),a           ; Set new color
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt        
	    pop     bc
	    pop     af
        ei
        ret        
1:        
        ld      a, 151          ; Next raster line
        out     (c),a           ; Set line to fire IRQ on
        ld      bc,0d020h       ; VIC border color
        ld      a,(border)      ; Get border color          
        out     (c),a           ; Set new color
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt        
	    pop     bc
	    pop     af
        ei
        ret
       