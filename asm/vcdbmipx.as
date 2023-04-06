;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set pixel in 640 x 480 bit map mode.  Math and local VDC I/O optimized for speed.
;

psect   text
global  _setpixivdc

_setpixivdc:

psect   data

;fast pixel look up using x mod 8 as index into bit table

bittable:

defb    -128
defb    64
defb    32
defb    16
defb    8
defb    4
defb    2
defb    1

psect   text
global  _vdcdispmem

        pop     hl              ;return address
        pop     bc              ;x
        pop     de              ;y
        push    de
        push    bc
        push    hl

        ld      a,l             ;save y low byte for odd/even test

        srl     d               ;y = y/2
        rr      e
                                ;calc (y * 80) + (x / 8) + bit map start
        ld      l,e             ;hl = y
        ld      h,d

        add     hl,hl           ;hl = y * 64;
        add     hl,hl
        add     hl,hl
        add     hl,hl
        add     hl,hl
        add     hl,hl

        ex      de,hl           ;de = y * 64; hl = y

        add     hl,hl           ;hl = y * 16
        add     hl,hl
        add     hl,hl
        add     hl,hl

        add     hl,de           ;hl = (y * 64)+(y * 16)

        ld      e,c             ;de = x
        ld      d,b

        srl     d               ;de = x / 8
        rr      e
        srl     d
        rr      e
        srl     d
        rr      e

        add     hl,de           ;hl = (y * 80) + (x / 8)
        ld      de,(_vdcdispmem)
        add     hl,de           ;hl = (y * 80) + (x / 8) + bit map offset

        and     01h             ;test bit 0 to determine odd/even
        jr      nz,3f           ;if y odd then
        ld      de,05370h       ; de = odd field offset of 21360 bytes
        add     hl,de           ; hl = hl+21360
3:
        ld      a,c             ;a = x low byte
        and     07h             ;a = x mod 8
        ld      d,0             ;de = x mod 8
        ld      e,a
        push    ix
        ld      ix,bittable     ;get address of bit table
        add     ix,de           ;ix = table addr + (x mod 8)
        ld      a,(ix+0)        ;a = bit to set from bit table
        pop     ix

        ld      d,18            ;set vdc update addr
        ld      e,h
        call    vdcset

        ld      d,19
        ld      e,l
        call    vdcset

        ld      d,31            ;get current byte
        call    vdcget

        or      e               ;a = current byte or bit table bit

        ld      d,18            ;set vdc update addr
        ld      e,h
        call    vdcset

        ld      d,19
        ld      e,l
        call    vdcset

        ld      d,31            ;set pixel
        ld      e,a
        call    vdcset

        ret

;set vdc reg, d = reg, e = val

vdcset:
        ld      bc,0d600h
        out     (c),d
1:
        in      d,(c)
        bit     7,d
        jr      z,1b
        inc     bc
        out     (c),e
        ret

;get vdc reg, d = reg, e = val

vdcget:

        ld      bc,0d600h
        out     (c),d
2:
        in      d,(c)
        bit     7,d
        jr      z,2b
        inc     bc
        in      e,(c)
        ret
