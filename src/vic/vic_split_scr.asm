;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with Z88DK-Z80ASM.
;
; C callable function used to set variables used by IRQ service.
; Bitmap can be on top or bottom.
;

SECTION code_clib
PUBLIC  vicSplitScr
PUBLIC  _vicSplitScr
PUBLIC  _irq1

; IRQ vector

vector	equ	0fdfeh

; Return address

return:

defw    0

; Raster start line for mode 1

raster1:

defw    0

; Control register in low byte and memory register in high byte for mode 1

ctrlReg1:

defw    0

; Raster start line for mode 2

raster2:

defw    0

; Control register in low byte and memory register in high byte for mode 2

ctrlReg2:

defw    0

; This code can be called from C to store values used in the IRQ service routine

vicSplitScr:
_vicSplitScr:
        pop     hl              ; Return address
        ld      (return),hl     ; Save return address
        pop     hl              ; Bitmap address
        ld      (ctrlReg2),hl   ; Save ctrlReg2 value
        pop     hl              ; raster2 value
        ld      (raster2),hl    ; Save raster2 value
        pop     de              ; ctrlReg1 value
        ld      (ctrlReg1),de   ; Save ctrlReg1 value
        pop     bc              ; raster1 value
        ld      (raster1),bc    ; Save raster1 value
        push    bc
        push    de
        ld      hl,(raster2)    ; Get saved raster2
        push    hl
        ld      hl,(ctrlReg2)   ; Get saved ctrlReg2
        push    hl
        ld      hl,(return)     ; Get saved return address
        push    hl
        ret

; This is the IRQ service routine which is looked up in the C code

_irq1:
        push    af
        push    bc
        push    hl
        ld      bc,0d012h       ; VIC raster line
        ld      a,(raster2)     ; Next raster line
        out     (c),a           ; Set line to fire IRQ on
        dec     c               ; bc = 0d011h VIC control register 1
        ld      hl,(ctrlReg1)
        out     (c),l           ; Set VIC control register 1
        ld      bc,0d018h       ; VIC memory control register
        out     (c),h           ; Set VIC memory control register
        ld      bc,irq2
        ld      (vector),bc     ; Change IRQ vector to irq2
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt
        pop     hl
        pop     bc
        pop     af
        ei
        ret
irq2:
        push    af
        push    bc
        push    de
        ld      bc,0d011h       ; VIC control register 1
        ld      de,(ctrlReg2)
        nop                     ; Add time to move raster into border
        nop
        nop
        nop
        out     (c),e           ; Set VIC memory control register
        ld      bc,0d018h       ; VIC memory control register
        out     (c),d           ; Set VIC memory control register
        ld      bc,0d012h       ; VIC raster line
        ld      a,(raster1)     ; Next raster line
        out     (c),a           ; Set line to fire IRQ on
        ld      bc,_irq1
        ld      (vector),bc     ; Change IRQ vector to _irq1
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt
        pop     de
        pop     bc
        pop     af
        ei
        ret
