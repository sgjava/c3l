;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Scroll VIC color memory up a line.
;

global  _scrollVicUpColAsm

psect   data

;return address

return:

defw    0

;line length

length:

defw    0

;source line

source:

defw    0

;dest line

dest:

defw    0

;line buffer to hold input line for output

buffer:

defs    40

psect   text

_scrollVicUpColAsm:
        pop     hl              ;return address
        ld      (return),hl     ;save return address
        pop     bc              ;dest port
        ld      (dest),bc       ;save dest
        pop     hl              ;line length
        ld      (length),hl     ;save line length             
        pop     de              ;lines in e
        push    de
        ld      d,l             ;line length in d    
        push    hl
        push    bc
        ld      hl,(return)     ;get saved return address        
        push    hl
        ld      hl,(dest)
1:
        ld      bc,40
        add     hl,bc           ;hl = hl_bc
        ld      (source),hl     ;save source         
        ld      bc,(source)     ;bc = source
        ld      hl,buffer       ;hl = buffer address
2:
		in		a,(c)           ;get color byte
		ld      (hl),a          ;save in buffer
	    inc     hl              ;hl = hl+1
	    inc     bc              ;bc = bc+1
        dec     d               ;d = d-1
        jr 		nz,2b           ;until 0
        ld      hl,(length)     ;hl = length
        ld      d,l             ;d = l
        ld      bc,(dest)       ;bc = dest
        ld      hl,buffer       ;hl = buffer address
3:
        ld      a,(hl)          ;a = buffer byte
        out     (c),a           ;set color byte                
	    inc     hl              ;hl = hl+1
	    inc     bc              ;bc = bc+1
        dec     d               ;d = d-1
        jr 		nz,3b           ;until 0
        ld      hl,(length)     ;hl = length
        ld      d,l             ;d = l
        ld      hl,(source)     ;hl = source
        ld      (dest),hl       ;save dest
        dec     e               ;e = e-1
        jr   	nz,1b           ;until 0       
        ret
       