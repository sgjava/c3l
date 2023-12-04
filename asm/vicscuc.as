;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Scroll VIC color memory up a line.
;

global  _scrollVicUpColAsm

psect   data

; Return address

return:

defw    0

; Line length

length:

defw    0

; Source line

source:

defw    0

; Dest line

dest:

defw    0

; Line buffer to hold input line for output

buffer:

defs    40

psect   text

_scrollVicUpColAsm:
        pop     hl              ; Return address
        ld      (return),hl     ; Save return address
        pop     bc              ; Dest port
        ld      (dest),bc       ; Save dest
        pop     hl              ; Line length
        ld      (length),hl     ; Save line length             
        pop     de              ; Lines in e
        push    de
        ld      d,l             ; Line length in d    
        push    hl
        push    bc
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ld      hl,(dest)
1:
        ld      bc,40
        add     hl,bc           ; hl = hl_bc
        ld      (source),hl     ; Save source         
        ld      bc,(source)     ; bc = source
        ld      hl,buffer       ; hl = buffer address
2:
        in      a,(c)           ; Get color byte
        ld      (hl),a          ; Save in buffer
        inc     hl              ; hl = hl+1
        inc     bc              ; bc = bc+1
        dec     d               ; d = d-1
        jr      nz,2b           ; Until 0
        ld      hl,(length)     ; hl = length
        ld      d,l             ; d = l
        ld      bc,(dest)       ; bc = dest
        ld      hl,buffer       ; hl = buffer address
3:
        ld      a,(hl)          ; a = buffer byte
        out     (c),a           ; set color byte                
        inc     hl              ; hl = hl+1
        inc     bc              ; bc = bc+1
        dec     d               ; d = d-1
        jr 		nz,3b           ; Until 0
        ld      hl,(length)     ; hl = length
        ld      d,l             ; d = l
        ld      hl,(source)     ; hl = source
        ld      (dest),hl       ; Save dest
        dec     e               ; e = e-1
        jr   	nz,1b           ; Until 0       
        ret
       