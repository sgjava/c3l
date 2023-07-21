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
        pop     hl              ; Return address
        ld      (return),hl     ; Save return address      
        pop     bc              ; Address
        pop     de              ; Length
        pop     hl              ; Color
        ld      a,l             ; a reg holds color
        push    hl
        push    de
        push    bc
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ld      l,a      
1:        
        out     (c),l           ; Set color memory
        inc     bc              ; Set for next address
        dec     de              ; Length -= 1
		ld		a,d
		or		e        
        jr      nz,1b 
        ret
       