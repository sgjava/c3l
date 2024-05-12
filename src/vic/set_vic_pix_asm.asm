;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set pixel in 320 x 200 VIC bit map mode. Math optimized for speed.
;

SECTION code_clib
PUBLIC  setVicPixAsm
PUBLIC  _setVicPixAsm

; Fast pixel look up using x mod 8 as index into bit table

setBitTable:

defb    -128, 64, 32, 16, 8, 4, 2, 1

; Fast pixel look up using x mod 8 as index into bit table

clearBitTable:

defb    127, -65, -33, -17, -9, -5, -3, -2

; Fast y * 40 look up using y as index into table

yTable:

defw    0, 40, 80, 120, 160, 200, 240, 280, 320, 360
defw    400, 440, 480, 520, 560, 600, 640, 680, 720, 760
defw    800, 840, 880, 920, 960, 1000, 1040, 1080, 1120, 1160
defw    1200, 1240, 1280, 1320, 1360, 1400, 1440, 1480, 1520, 1560
defw    1600, 1640, 1680, 1720, 1760, 1800, 1840, 1880, 1920, 1960
defw    2000, 2040, 2080, 2120, 2160, 2200, 2240, 2280, 2320, 2360
defw    2400, 2440, 2480, 2520, 2560, 2600, 2640, 2680, 2720, 2760
defw    2800, 2840, 2880, 2920, 2960, 3000, 3040, 3080, 3120, 3160
defw    3200, 3240, 3280, 3320, 3360, 3400, 3440, 3480, 3520, 3560
defw    3600, 3640, 3680, 3720, 3760, 3800, 3840, 3880, 3920, 3960
defw    4000, 4040, 4080, 4120, 4160, 4200, 4240, 4280, 4320, 4360
defw    4400, 4440, 4480, 4520, 4560, 4600, 4640, 4680, 4720, 4760
defw    4800, 4840, 4880, 4920, 4960, 5000, 5040, 5080, 5120, 5160
defw    5200, 5240, 5280, 5320, 5360, 5400, 5440, 5480, 5520, 5560
defw    5600, 5640, 5680, 5720, 5760, 5800, 5840, 5880, 5920, 5960
defw    6000, 6040, 6080, 6120, 6160, 6200, 6240, 6280, 6320, 6360
defw    6400, 6440, 6480, 6520, 6560, 6600, 6640, 6680, 6720, 6760
defw    6800, 6840, 6880, 6920, 6960, 7000, 7040, 7080, 7120, 7160
defw    7200, 7240, 7280, 7320, 7360, 7400, 7440, 7480, 7520, 7560
defw    7600, 7640, 7680, 7720, 7760, 7800, 7840, 7880, 7920, 7960

; Return address

return:

defw    0

; Bitmap memory

bmpMem:

defw    0

; x

x:

defw    0

; y

y:

defw    0

; Color

color:

defw    0

setVicPixAsm:
_setVicPixAsm:
        pop     hl               ; Return address
        ld      (return),hl      ; Save return address
        pop     hl               ; Bitmap address
        ld      (bmpMem),hl      ; Save bitmap address
        pop     hl               ; Color
        ld      (color),hl       ; Save color
        pop     de               ; y
        ld      (y),de           ; Save y
        pop     bc               ; x
        ld      (x),bc           ; Save x
        push    bc
        push    de
        ld      hl,(color)       ; Get saved color
        push    hl
        ld      hl,(bmpMem)      ; Get saved bitmap address
        push    hl
        ld      hl,(return)      ; Get saved return address
        push    hl
        ld      a,e              ; y low byte (d should be 0x00)
        and     0f8h             ; y & 0xf8
        ld      e,a              ; Save in e         
        ld      hl,yTable        ; Load lookup table address into hl
        add     hl,de            ; hl = hl + de
        add     hl,de            ; hl = hl + de        
        ld      a,(hl)           ; a = table value low byte
        inc     hl               ; hl = hl + 1
        ld      h,(hl)           ; h = table value high byte 
        ld      l,a              ; l = table value low byte
        ld      a,c
        and     0f8h
        ld      c,a              ; x low & 0xf8 (no need to and high byte with 0x01)
        add     hl,bc
        ld      de,(y)        
        ld      a,e              ; a = y low byte
        and     07h              ; a = y & 0x07
        ld      e,a
        add     hl,de
        ld      de,(bmpMem)      ; de = bitmap offset
        add     hl,de            ; hl = (y & 0xf8) + (x & 0x1f8) + (y & 0x07) + bit map offset
        ex      de,hl            ; Swap de and hl
        ld      a,(x)
        and     07h              ; a = x mod 8              
        ld      b,0              ; b = x mod 8 high byte
        ld      c,a              ; c = x mod 8 low byte    
        ld      a,(color)        ; Get color
        cp      0
        jr      z,clear          ; Zero color means clear pixel  
        
        ld      hl,setBitTable   ; Load bit table address into hl
        add     hl,bc            ; hl = bit table addr + (x mod 8)
        ld      a,(hl)           ; a = bit to set from bit table 
        ex      de,hl            ; Swap de and hl
        ld      e,(hl)           ; Get bitmap byte
        or      e                ; a = current byte or with bit table bit
        ld      (hl),a
        ret        
clear:
        ld      hl,clearBitTable ; Load bit table address into hl
        add     hl,bc            ; hl = bit table addr + (x mod 8)
        ld      a,(hl)           ; a = bit to set from bit table 
        ex      de,hl            ; Swap de and hl
        ld      e,(hl)           ; Get bitmap byte
        and     e                ; a = current byte or with bit table bit
        ld      (hl),a
        ret
        
