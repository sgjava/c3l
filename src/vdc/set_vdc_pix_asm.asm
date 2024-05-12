;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set pixel in 640 x 200 bit map mode. Math and local VDC I/O optimized for speed.
;

SECTION code_clib
PUBLIC  setVdcPixAsm
PUBLIC  _setVdcPixAsm

; Fast pixel look up using x mod 8 as index into bit table

setBitTable:

defb    -128, 64, 32, 16, 8, 4, 2, 1

; Fast pixel look up using x mod 8 as index into bit table

clearBitTable:

defb    127, -65, -33, -17, -9, -5, -3, -2

; Fast y * 80 look up using y as index into table

yTable:

defw    0, 80, 160, 240, 320, 400, 480, 560, 640, 720
defw    800, 880, 960, 1040, 1120, 1200, 1280, 1360, 1440, 1520
defw    1600, 1680, 1760, 1840, 1920, 2000, 2080, 2160, 2240, 2320
defw    2400, 2480, 2560, 2640, 2720, 2800, 2880, 2960, 3040, 3120
defw    3200, 3280, 3360, 3440, 3520, 3600, 3680, 3760, 3840, 3920
defw    4000, 4080, 4160, 4240, 4320, 4400, 4480, 4560, 4640, 4720
defw    4800, 4880, 4960, 5040, 5120, 5200, 5280, 5360, 5440, 5520
defw    5600, 5680, 5760, 5840, 5920, 6000, 6080, 6160, 6240, 6320
defw    6400, 6480, 6560, 6640, 6720, 6800, 6880, 6960, 7040, 7120
defw    7200, 7280, 7360, 7440, 7520, 7600, 7680, 7760, 7840, 7920
defw    8000, 8080, 8160, 8240, 8320, 8400, 8480, 8560, 8640, 8720
defw    8800, 8880, 8960, 9040, 9120, 9200, 9280, 9360, 9440, 9520
defw    9600, 9680, 9760, 9840, 9920, 10000, 10080, 10160, 10240, 10320
defw    10400, 10480, 10560, 10640, 10720, 10800, 10880, 10960, 11040, 11120
defw    11200, 11280, 11360, 11440, 11520, 11600, 11680, 11760, 11840, 11920
defw    12000, 12080, 12160, 12240, 12320, 12400, 12480, 12560, 12640, 12720
defw    12800, 12880, 12960, 13040, 13120, 13200, 13280, 13360, 13440, 13520
defw    13600, 13680, 13760, 13840, 13920, 14000, 14080, 14160, 14240, 14320
defw    14400, 14480, 14560, 14640, 14720, 14800, 14880, 14960, 15040, 15120
defw    15200, 15280, 15360, 15440, 15520, 15600, 15680, 15760, 15840, 15920

; Return address

return:

defw    0

; Bitmap memory

bmpMem:

defw    0

; Color

color:

defw    0


setVdcPixAsm:
_setVdcPixAsm:
        pop     hl              ; Return address
        ld      (return),hl     ; Save return address
        pop     hl              ; Bitmap address
        ld      (bmpMem),hl     ; Save bitmap address
        pop     hl              ; Color value
        ld      (color),hl      ; Save color
        pop     de              ; y value
        pop     bc              ; x value
        push    bc
        push    de
        push    hl
        ld      hl,(bmpMem)     ; Save bitmap address
        push    hl
        ld      hl,(return)     ; Get saved return address        
        push    hl
        ld      hl,yTable       ; Load lookup table address into hl
        add     hl,de           ; hl = hl + de
        add     hl,de           ; hl = hl + de
        ld      a,(hl)          ; a = table value low byte
        inc     hl              ; hl = hl + 1
        ld      h,(hl)          ; h = table value high byte 
        ld      l,a             ; l = table value low byte
        ld      a,c             ; a = x low byte
        and     07h             ; a = x mod 8
        srl     b               ; bc = x / 8
        rr      c
        srl     b
        rr      c
        srl     b
        rr      c
        add     hl,bc            ; hl = (y * 80) + (x / 8)
        ld      de,(bmpMem)      ; de = bitmap offset
        add     hl,de            ; hl = (y * 80) + (x / 8) + bit map offset
        ex      de,hl            ; Swap de and hl
        ld      b,0              ; bc = x mod 8
        ld      c,a
        ld      a,(color)        ; Get color
        cp      0
        jr      z,clear          ; Zero color means clear pixel
        ld      hl,setBitTable   ; Load bit table address into hl
        add     hl,bc            ; hl = bit table addr + (x mod 8)
        ld      a,(hl)           ; a = bit to set from bit table
        ex      de,hl            ; Swap de and hl
        ld      bc,0d600h        ; Prime pump with VDC status register
        ld      d,18             ; Set VDC update addr
        ld      e,h
        call    vdcSet
        ld      d,19
        ld      e,l
        call    vdcSet
        ld      d,31             ;Get current byte
        call    vdcGet
        or      e                ; a = current byte or with bit table bit
        ld      d,18             ; Set VDC update addr
        ld      e,h
        call    vdcSet
        ld      d,19
        ld      e,l
        call    vdcSet
        ld      d,31             ; Set pixel
        ld      e,a
        call    vdcSet
        ret
clear:
        ld      hl,clearBitTable ; Load bit table address into hl
        add     hl,bc            ; hl = bit table addr + (x mod 8)
        ld      a,(hl)           ; a = bit to set from bit table
        ex      de,hl            ; Swap de and hl
        ld      bc,0d600h        ; Prime pump with VDC status register
        ld      d,18             ; Set VDC update addr
        ld      e,h
        call    vdcSet
        ld      d,19
        ld      e,l
        call    vdcSet
        ld      d,31             ; Get current byte
        call    vdcGet
        and      e               ; a = current byte or with bit table bit
        ld      d,18             ; Set VDC update addr
        ld      e,h
        call    vdcSet

        ld      d,19
        ld      e,l
        call    vdcSet
        ld      d,31             ; Set pixel
        ld      e,a
        call    vdcSet
        ret

; Set VDC register: d = reg, e = val

vdcSet:
        out     (c),d
rep1:
        in      d,(c)
        bit     7,d
        jr      z,rep1
        inc     c
        out     (c),e
        dec     c
        ret

;Get VDC register: d = reg, e = val

vdcGet:
        out     (c),d
rep2:
        in      d,(c)
        bit     7,d
        jr      z,rep2
        inc     c
        in      e,(c)
        dec     c
        ret
