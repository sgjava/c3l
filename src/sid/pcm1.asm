;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with z88dk-z80asm.
;
; Play 1 bit pulse wave encoded data using SID master volume.
;
; Minimum playback rate 4 KHz
; Maximum playback rate ~18 KHz
;

SECTION code_clib
PUBLIC  playPcm1Sid
PUBLIC  _playPcm1Sid

; Return address

return:

defw    0

; Sample amplitude can be 1 - 15

amp:

defw    0

start:

defw    0

playPcm1Sid:
_playPcm1Sid:
        pop     hl              ; Return address?
        ld      (return),hl     ; Save return address
        pop     hl              ; Sample amplitude
        ld      (amp),hl        ; Save sample amplitude
        pop     de              ; Sample length
        pop     bc              ; Sample start address
        ld      (start), bc     ; Save sample start address
        push    bc
        push    de
        ld      (amp),hl        ; Save sample amplitude
        push    hl
        ld      hl,(return)     ; Get saved return address        
        push    hl
        push    ix              ; Preserve ix
        ex      de,hl           ; Swap de and hl (sample length)
        ld      a,h             ; Handle h having zero value
        or      h
        jr      nz,if1          ; h != 0?
        inc     h               ; h = h+1
        if1:        
        ld      ix,(start)                   
        rep1:                   ; Repeat
        ld      d,(ix+0)        ; d = Sample byte
        ld      e,08h           ; e = 8 bits to count
        rep2:              
        ld      bc,0dd0dh       ; bc = CIA 2 ICR
        rep3:                   ; Repeat
        in      a,(c)           ; a = CIA 2 ICR value
        bit     0,a             ;
        jr      z,rep3          ; Until interrupt flag set
        ld      a,00h           ; a = volume for 0 bits
        rlc     d               ; Set sample bit
        jr      nc,endif1       ; if carry=1 then
        ld      a,(amp)         ; a = volume for 1 bits
        endif1:
        ld      bc,0d418h       ; bc = SID volume address
        out     (c),a           ; Set volume
        dec     e               ; e = e-1
        jr      nz,rep2         ; Until e = 0
        inc     ix              ; ix = ix+1
        dec     l               ; l = l-1
        jr      nz,rep1         ; Until l = 0
        dec     h               ; h = h-1
        jr      nz,rep1         ; Until h = 0
        pop     ix              ; Restore ix
        ret
