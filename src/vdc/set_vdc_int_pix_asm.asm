;
; Copyright (c) Steven P. Goldsmith. All rights reserved.
;
; Assembled with HI-TECH C 3.09 (CP/M-80) ZAS.
;
; Set pixel in 640 x 200 bit map mode. Math and local VDC I/O optimized for speed.
;

SECTION code_clib
PUBLIC  setVdcIntPixAsm
PUBLIC  _setVdcIntPixAsm

; Fast pixel look up using x mod 8 as index into bit table

SECTION	code_clib
PUBLIC	setVdcIntPixAsm
PUBLIC	_setVdcIntPixAsm

; Fast pixel look up using x mod 8 as index into bit table

setBitTable:
	defb	-128, 64, 32, 16, 8, 4, 2, 1

; Fast pixel look up using x mod 8 as index into bit table

clearBitTable:
	defb	127, -65, -33, -17, -9, -5, -3, -2

; Return address

return:
	defw	0

; Bitmap memory

bmpMem:
	defw	0

; Color

color:
	defw	0

setVdcIntPixAsm:
_setVdcIntPixAsm:
	pop		hl						; Return address
	ld			(return), hl		; Save return address
	pop		hl						; Bitmap address
	ld			(bmpMem), hl	; Save bitmap address
	pop		hl						; Color value
	ld			(color), hl			; Save color
	pop		de						; y value
	pop		bc						; x value
	push		bc
	push		de
	push		hl
	ld			hl, (bmpMem)	; Save bitmap address
	push		hl
	ld			hl, (return)		; Get saved return address
	push		hl
	ld			a, e					; Save y low byte for odd/even test
	srl			d						; y = y / 2
	rr			e
										; Calc (y * 80) + (x / 8) + bit map start
	ld			l, e					; hl = y
	ld			h, d
	add		hl, hl					; hl = y * 64
	add		hl, hl
	add		hl, hl
	add		hl, hl
	add		hl, hl
	add		hl, hl
	ex			de, hl				; de = y * 64; hl = y
	add		hl, hl					; hl = y * 16
	add		hl, hl
	add		hl, hl
	add		hl, hl
	add		hl, de				; hl = (y * 64) + (y * 16)
	ld			e, c					; de = x
	ld			d, b
	srl			d						; de = x / 8
	rr			e
	srl			d
	rr			e
	srl			d
	rr			e
	add		hl, de				; hl = (y * 80) + (x / 8)
	ld			de, (bmpMem)
	add		hl, de				; hl = (y * 80) + (x / 8) + bit map offset
	and		01h					; Test bit 0 to determine odd/even
	jr			nz, even			; If y odd then
	ld			de, 05370h		; de = odd field offset of 21360 bytes
	add		hl, de				; hl = hl + 21360
even:
	ex			de, hl				; Swap de and hl
	ld			b, 0             		; bc = x mod 8
	ld			c, a
	ld			a, (color)			; Get color
	cp			0
 	jr			z, clear				; Zero color means clear pixel
 	ld			hl, setBitTable	; Load bit table address into hl
 	add		hl, bc           	 	; hl = bit table addr + (x mod 8)
	ld			a, (hl)				; a = bit to set from bit table
	ex			de, hl           		; Swap de and hl
	ld			bc, 0d600h      ; Prime pump with VDC status register
	ld			d, 18				; Set VDC update addr
	ld			e, h
	call		vdcSet
	ld			d, 19
	ld			e, l
	call		vdcSet
	ld			d, 31           		 ; Get current byte
	call		vdcGet
	or			e          			     ; a = current byte or with bit table bit
	ld			d, 18       		     ; Set VDC update addr
	ld			e, h
	call		vdcSet
	ld			d, 19
	ld			e, l
	call		vdcSet
	ld			d, 31             ; Set pixel
	ld			e, a
	call		vdcSet
	ret
clear:
	ld			hl, clearBitTable	; Load bit table address into hl
	add		hl, bc			; hl = bit table addr + (x mod 8)
	ld			a, (hl)			; a = bit to set from bit table
	ex			de, hl			; Swap de and hl
	ld			bc, 0d600h		; Prime pump with VDC status register
	ld			d, 18			; Set VDC update addr
	ld			e, h
	call		vdcSet
	ld			d, 19
	ld			e, l
	call		vdcSet
	ld			d, 31			; Get current byte
	call		vdcGet
	and		e				; a = current byte or with bit table bit
	ld			d, 18			; Set VDC update addr
	ld			e, h
	call		vdcSet
	ld			d, 19
	ld			e, l
	call		vdcSet
	ld			d, 31			; Set pixel
	ld			e, a
	call		vdcSet
	ret

; Set VDC register: d = reg, e = val

vdcSet:
	out		(c), d
rep1:
	in		d, (c)
	bit		7, d
	jr		z, rep1
	inc		c
	out		(c), e
	dec		c
	ret

; Get VDC register: d = reg, e = val

vdcGet:
	out		(c), d
rep2:
	in		d, (c)
	bit		7, d
	jr		z, rep2
	inc		c
	in		e, (c)
	dec		c
	ret
