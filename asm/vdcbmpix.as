;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set pixel in 640 x 200 bit map mode.  Math and local VDC optimized for speed.
;

psect   text
global  _setpixvdc

_setpixvdc:

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
