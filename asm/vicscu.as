;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Scroll VIC text memory up a line.
;

global  _scrollVicUpAsm

psect   data

;return address

return:

defw    0

;line length

length:

defw    0

;lines

lines:

defw    0

;dest line

dest:

defw    0

psect   text

_scrollVicUpAsm:
        pop     hl              ;return address
        ld      (return),hl     ;save return address
        pop     bc              ;dest address
        ld      (dest),bc       ;save dest address
        pop     hl              ;line length
        ld      (length),hl     ;save line length             
        pop     de              ;lines
        ld      (lines),de      ;save lines        
        push    de
        push    hl
        push    bc
        ld      hl,(return)     ;get saved return address        
        push    hl
        ld      hl,(lines)      ;prime lines     
1:
        ld      (lines),hl
        ld      hl,(dest)       ;hl is source
        ld      bc,40
        add     hl,bc           ;hl = hl+bc
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
        add     hl,bc           ;hl = hl_bc
        ld      (dest),hl       ;save dest
        ld      hl,(lines)
        dec     l               ;l = l-1
        jr   	nz,1b           ;until 0          
        ret
        