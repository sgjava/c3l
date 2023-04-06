;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Play 4 bit pulse wave encoded data using SID master volume
;

global  _playpcm4
global  ncsv, cret, indir

psect   text

_playpcm4:

global  csv

call    csv
ld      l,(ix+6)        ;sample start addr
ld      h,(ix+7)
ld      e,(ix+8)        ;sample length
ld      d,(ix+9)

rep1:                   ;repeat

ld      bc,0dd0dh       ; bc = timea2 addr

rep2:                   ; repeat

in      a,(c)           ;  a = timer lo
bit     0,a             ;
jr      z,rep2          ; until interrupt flag set
ld      a,(hl)          ; a = sample byte
rrca                    ; a = a div 16
rrca                    ;
rrca                    ;
rrca                    ;
and     0fh             ; 4 bit nibble
ld      bc,0d418h       ; bc = sidvol addr
out     (c),a           ; set volume
ld      bc,0dd0dh       ; bc = cia 2 icr

rep3:                   ; repeat

in      a,(c)           ;  a = timer lo
bit     0,a             ;
jr      z,rep3          ; until interrupt flag set
ld      a,(hl)          ; a = sample byte
and     0fh             ; a = a and 15
ld      bc,0d418h       ; bc = sidvol addr
out     (c),a           ; set volume
inc     hl              ; hl = hl+1
dec     e               ;
jr      nz,rep1         ;
dec     d               ; de = de-1
jr      nz,rep1         ;until de = 0
jp      cret
