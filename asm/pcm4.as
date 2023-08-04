;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Play 4 bit pulse wave encoded data using SID master volume.
;

global  _playPcm4Sid
psect   text

_playPcm4Sid:
        pop     bc              ; Return address
        pop     hl              ; Sample start address
        pop     de              ; Sample length
        push    de
        push    hl
        push    bc
        rep1:                   ; Repeat
        ld      bc,0dd0dh       ; bc = CIA 2 ICR
        rep2:                   ; Repeat
        in      a,(c)           ; a = CIA 2 ICR value
        bit     0,a             ;
        jr      z,rep2          ; Until interrupt flag set
        ld      a,(hl)          ; a = sample byte
        rrca                    ; a = a div 16
        rrca                    ;
        rrca                    ;
        rrca                    ;
        and     0fh             ; 4 bit nibble
        ld      bc,0d418h       ; bc = SID volume address
        out     (c),a           ; Set volume
        ld      bc,0dd0dh       ; bc = CIA 2 ICR
        rep3:                   ; Repeat
        in      a,(c)           ; a = CIA 2 ICR value
        bit     0,a             ;
        jr      z,rep3          ; Until interrupt flag set
        ld      a,(hl)          ; a = sample byte
        and     0fh             ; a = a and 15
        ld      bc,0d418h       ; bc = SID volume address
        out     (c),a           ; Set volume
        inc     hl              ; hl = hl+1
        dec     e               ;
        jr      nz,rep1         ;
        dec     d               ; de = de-1
        jr      nz,rep1         ; Until de = 0
        ret
