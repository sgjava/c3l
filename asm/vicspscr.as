;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; C callable function used to set variables used by IRQ service.
; Bitmap can be on top or bottom.
;
; For some reason the following hangs the code (so more expensive push and pop are used):
;
; ex af,af'
; exx
;

global  _vicSplitScr

; IRQ vector

vector	equ	0fdfeh

psect   data

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

psect   text

; This code can be called from C to store values used in the IRQ service routine

_vicSplitScr:
        pop     hl              ; Return address
        ld      (return),hl     ; Save return address      
        pop     bc              ; raster1 value
        ld      (raster1),bc    ; Save raster1 value              
        pop     de              ; ctrlReg1 value
        ld      (ctrlReg1),de   ; Save ctrlReg1 value              
        pop     hl              ; raster2 value
        ld      (raster2),hl    ; Save raster2 value
        pop     hl              ; Bitmap address
        ld      (ctrlReg2),hl   ; Save ctrlReg2 value            
        push    hl       
        ld      hl,(raster2)    ; Get saved raster2        
        push    hl                   
        push    de
        push    bc
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ret     

; This is the IRQ service routine which is looked up in the C code

irq1:
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
        ld      bc,irq1     
        ld      (vector),bc     ; Change IRQ vector to irq1        
        ld      bc,0d019h
        ld      a,0ffh
        out     (c),a           ; Ack raster interrupt     
        pop     de
        pop     bc
        pop     af     
        ei
        ret
       