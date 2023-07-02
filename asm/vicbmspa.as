;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set pixel in 320 x 200 VIC bit map mode. Math optimized for speed.
;

global  _setVicPixAsm

psect   data

;fast pixel look up using x mod 8 as index into bit table

setBitTable:

defb    -128, 64, 32, 16, 8, 4, 2, 1

;fast pixel look up using x mod 8 as index into bit table

clearBitTable:

defb    127, -65, -33, -17, -9, -5, -3, -2

;fast y * 40 look up using y as index into table

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

;return address

return:

defw    0

;Bitmap memory

bmpMem:

defw    0

;x

x:

defw    0

;y

y:

defw    0

;color

color:

defw    0

psect   text
_setVicPixAsm:

        pop     hl              ;return address
        ld      (return),hl     ;save return address      
        pop     bc              ;x
        ld      (x),bc          ;save x
        pop     de              ;y
        ld      (y),de          ;save y
        pop     hl              ;color
        ld      (color),hl      ;save color
        pop     hl              ;bitmap address
        ld      (bmpMem),hl     ;save bitmap address          
        push    hl
        ld      hl,(color)      ;get saved color        
        push    hl                   
        push    de
        push    bc
        ld      hl,(return)     ;get saved return address        
        push    hl

        ld      a,e             ;y low byte (e should be 0x00)
        and     0f8h            ;y & 0xf8
        ld      e,a             ;save in e         
        ld      hl,yTable       ;load lookup table address into hl
        add     hl,de           ;hl = hl + de
        add     hl,de           ;hl = hl + de        
        ld      a,(hl)          ;a = table value low byte
        inc     hl              ;hl = hl + 1
        ld      h,(hl)          ;h = table value high byte 
        ld      l,a             ;l = table value low byte
        ld      a,c
        and     0f8h
        ld      c,a             ;x low & 0xf8 (no need to and high byte with 0x01)
        add     hl,bc
        ld      de,(y)        
        ld      a,e             ;a = y low byte
        and     07h             ;a = y & 0x07
        ld      e,a
        add     hl,de

        ld      de,(bmpMem)      ;de = bitmap offset
        add     hl,de            ;hl = (y & 0xf8) + (x & 0x1f8) + (y & 0x07) + bit map offset
        ex      de,hl            ;swap de and hl
        ld      a,(x)
        and     07h              ;a = x mod 8              
        ld      b,0              ;b = x mod 8 high byte
        ld      c,a              ;c = x mod 8 low byte    
        ld      a,(color)        ;get color
        cp      0
        jr      z,1f             ;zero color means clear pixel  
        
        ld      hl,setBitTable   ;load bit table address into hl
        add     hl,bc            ;hl = bit table addr + (x mod 8)
        ld      a,(hl)           ;a = bit to set from bit table 
        ex      de,hl            ;swap de and hl
        ld      e,(hl)           ;get bitmap byte
        or      e                ;a = current byte or with bit table bit
        ld      (hl),a
        ret
        
1:
        ld      hl,clearBitTable ;load bit table address into hl
        add     hl,bc            ;hl = bit table addr + (x mod 8)
        ld      a,(hl)           ;a = bit to set from bit table 
        ex      de,hl            ;swap de and hl
        ld      e,(hl)           ;get bitmap byte
        and     e                ;a = current byte or with bit table bit
        ld      (hl),a
        ret
        