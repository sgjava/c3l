;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set VIC MMU bank
;

global  _vicMmuBank
psect   text

_vicMmuBank:
        pop     hl              ; Return address
        pop     de              ; VIC bank 0 (0x00) or 1 (0x40)
        push    de
        push    hl
        di                      ; Disable interrupts
        ld      hl,0ff00h       ; C128 configuration register
        ld      a,7eh           ; MMU I/O bit to allow Z80 IN/OUT to work
        ld      (hl),a          ; Do it
        ld      bc,0d506h       ; MMU RAM configuration register
        in      a,(c)           ; Get current value
        and     0bfh            ; Keep all MMU RCR bits except 6
        or      e               ; 0x00 for bank 0 and 0x40 for bank 1
        out     (c),a           ; Do it
        ld      a,07fh          ; MMU I/O bit set to ROM/RAM
        ld      (hl),a          ; Do it
        ei                      ; Enable interrupts
        ret
  