;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Fill VIC color memory.
;

SECTION code_clib
PUBLIC  fillVicMemCol
PUBLIC  _fillVicMemCol

;return address

return:

defw    0

fillVicMemCol:
_fillVicMemCol:
        pop     hl              ; Return address?
        ld      (return),hl     ; Save return address      
        pop     hl              ; Color
        ld      a,l             ; a reg holds color
        pop     de              ; Length        
        pop     bc              ; Address
        push    bc
        push    de
        push    hl
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ld      l,a      
rep1:        
        out     (c),l           ; Set color memory
        inc     bc              ; Set for next address
        dec     de              ; Length -= 1
        ld      a,d
        or      e        
        jr      nz,rep1 
        ret
       