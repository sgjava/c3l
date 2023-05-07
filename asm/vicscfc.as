;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Fill VIC color memory.
;

global  _fillVicMemCol

psect   data

;return address

return:

defw    0

psect   text

_fillVicMemCol:
        pop     hl              ;return address
        ld      (return),hl     ;save return address      
        pop     bc              ;address
        pop     de              ;length
        pop     hl              ;color
        ld      a,l             ;a reg holds color
        push    hl
        push    de
        push    bc
        ld      hl,(return)     ;get saved return address        
        push    hl
        ld      l,a      
1:        
        out     (c),l           ;set color memory
        inc     bc              ;set for next address
        dec     de              ;length -= 1
		ld		a,d
		or		e        
        jr      nz,1b 
        ret
       