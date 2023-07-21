;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Scroll VIC text memory up a line.
;

global  _scrollVicUpAsm

psect   data

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

psect   text

_scrollVicUpAsm:
        pop     hl              ; Return address
        ld      (return),hl     ; Save return address
        pop     bc              ; Dest address
        ld      (dest),bc       ; Save dest address
        pop     hl              ; Line length
        ld      (length),hl     ; Save line length             
        pop     de              ; Lines
        ld      (lines),de      ; Save lines        
        push    de
        push    hl
        push    bc
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ld      hl,(lines)      ; Prime lines     
1:
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
        jr   	nz,1b           ; Until 0          
        ret
        