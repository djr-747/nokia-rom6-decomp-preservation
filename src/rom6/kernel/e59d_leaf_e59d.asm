; ROM6 0xE59D LEAF_E59D -- 29w, symbols.yaml data_word.
; Evidence: Bound E59D-E5B9 (exit retd FE00@E5B7 + delays E5B8-E5B9 objdump-aligned); entries 2x F274 calld E2D7/E31B word-verified; adjacency E583-span true end E59C, no overlap; bytes E735 8
; ORIGIN 0xE59D
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @E59D e735 mvmm   ar3,ar5
	mvmm   ar3,ar5
	; @E59E 8293 sth    a,*ar3+
	sth    a,*ar3+
	; @E59F 4808 ldm    al,a
	ldm    al,a
	; @E5A0 9a9f sth    a,15,*ar3+
	sth    a,15,*ar3+
	; @E5A1 f062 ld     #16383,16,a
	ld     #16383,16,a
	; @E5A3 ec0e rpt    #14
	rpt    #14
	; @E5A4 1e82 subc   *ar2,a
	subc   *ar2,a
	; @E5A5 8083 stl    a,*ar3
	stl    a,*ar3
	; @E5A6 a518 mpy    *ar3,*ar2+,b
	mpy    *ar3,*ar2+,b
	; @E5A7 208a mpy    *ar2-,a
	mpy    *ar2-,a
	; @E5A8 3562 maca   0x62,b
	maca   0x62,b
	; @E5A9 f684 neg    b,a
	neg    b,a
	; @E5AA 5066 dadd   0x66,a
	dadd   0x66,a
	; @E5AB 3193 mpya   *ar3+
	mpya   *ar3+
	; @E5AC 4808 ldm    al,a
	ldm    al,a
	; @E5AD 9a1f sth    a,15,*ar3
	sth    a,15,*ar3
	; @E5AE 2093 mpy    *ar3+,a
	mpy    *ar3+,a
	; @E5AF 3562 maca   0x62,b
	maca   0x62,b
	; @E5B0 838b sth    b,*ar3-
	sth    b,*ar3-
	; @E5B1 490b ldm    bl,b
	ldm    bl,b
	; @E5B2 9b9f sth    b,15,*ar3+
	sth    b,15,*ar3+
	; @E5B3 a55b mpy    *ar3-,*ar5+,b
	mpy    *ar3-,*ar5+,b
	; @E5B4 208d mpy    *ar5-,a
	mpy    *ar5-,a
	; @E5B5 3562 maca   0x62,b
	maca   0x62,b
	; @E5B6 a493 mpy    *ar3+,*ar5,a
	mpy    *ar3+,*ar5,a
	; @E5B7 fe00 retd
	retd
	; @E5B8 3562 maca   0x62,b
	maca   0x62,b
	; @E5B9 f642 ld     b,2,a
	ld     b,2,a
