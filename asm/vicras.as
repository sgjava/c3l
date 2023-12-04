;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; This function can be called by C to sev border and stripe values. Interrupt
; code to be called by 0xfdfd vector.
;

global  _vicRas

psect   data

; Border color

border:

defw    0

; Raster color stripe

stripe:

defw    0

psect   text

; This code can be called from C to store values used in the IRQ service routine

_vicRas:
        pop     hl              ; Return address
        pop     bc              ; Border color
        pop     de              ; Stripe color
        ld      (border),bc     ; Save border color 
        ld      (stripe),de     ; Save stripe color         
        push    de
        push    bc
        push    hl
        ret       

; This is the IRQ service routine which is looked up in the C code
 
        push    af              ; Only pushing 4 bytes on the stack, so no creating new SP
        push    bc
        ld      bc,0d012h       ; VIC raster line
        in      a,(c)           ; Get current line
        cp      141             ; This is the start line
        jp      nz, 1f          ; Not 141 then jump
        ld      a, 169          ; Next raster line
        out     (c),a           ; Set line to fire IRQ on        
        ld      bc,0d020h       ; VIC border color
        ld      a,(stripe)
        nop                     ; Fix jitter
        nop
        nop
        nop
        nop
        nop
        out     (c),a           ; Set stripe color
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt        
	    pop     bc
	    pop     af
        ei
        ret        
1:        
        ld      a, 141          ; Next raster line
        out     (c),a           ; Set line to fire IRQ on
        ld      bc,0d020h       ; VIC border color
        ld      a,(border)      ; Get border color
        nop                     ; Fix jitter
        nop
        nop
        nop
        nop
        nop
        out     (c),a           ; Set new color
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt        
	    pop     bc
	    pop     af
        ei
        ret
       