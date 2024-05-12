;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Scroll VIC text memory up a line.
;

SECTION code_clib
PUBLIC  scrollVicUpAsm
PUBLIC  _scrollVicUpAsm

; Return address

return:

defw    0

; Line length

length:

defw    0

; Lines

lines:

defw    0

; Dest line

dest:

defw    0

scrollVicUpAsm:
_scrollVicUpAsm:
        pop     hl              ; Return address?
        ld      (return),hl     ; Save return address
        pop     de              ; Lines
        ld      (lines),de      ; Save lines 
        pop     hl              ; Line length
        ld      (length),hl     ; Save line length 
        pop     bc              ; Dest address
        ld      (dest),bc       ; Save dest address
        push    bc        
        push    hl
        push    de       
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ld      hl,(lines)      ; Prime lines     
rep1:
        ld      (lines),hl
        ld      hl,(dest)       ; hl is source
        ld      bc,40
        add     hl,bc           ; hl = hl+bc
        ld      de,(dest)
        ld      bc,(length)
        ld      a,(hl)
        ld      (de),a
        inc     hl
        inc     de
        dec     bc
        ldir
        ld      hl,(dest)
        ld      bc,40
        add     hl,bc           ; hl = hl_bc
        ld      (dest),hl       ; Save dest
        ld      hl,(lines)
        dec     l               ; l = l-1
        jr   	nz,rep1         ; Until 0          
        ret
