; ROM6 0xE06A MAC_KERNEL_SHARED -- 56w, symbols.yaml data_word.
; Evidence: Entry E712 E713 F062 8000; 3x callers F274 @E24C/E256/E260; BOUND CORRECTED entry-linear: straight- line to first exit retd @0xE09F, bound E06A-E0A1 (incl delay); was E0EC (overcla
; Pool: max a (F486 MAX_ACC: catalog row exists but no oracle leaf anywhere). Secondaries grounded-or-flagged (duals/op_mac_dual; maca/op_maca_smem; srccd/op_srccd leaf; stl-shift/ld-shift/sfta; rptbd flagged). stays .asm, bytes verified.
; ORIGIN 0xE06A
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar1,ar2
	mvmm   ar1,ar3
	ld     #-32768,16,a
	stm    #-78,ar0
	mpy    *ar3+,*ar4+,b
	rptbd  0xe07d
	mac    *ar3+,*ar4+,b
	mac    *ar3+,*ar4+,b
	rpt    #75
	mac    *ar3+,*ar4+,b
	mac    *ar3+0%,*ar4+0%,b
	max    a
	sub    a,b
	srccd  *ar5,beq
	mpy    *ar2,*ar4+,b
	mac    *ar3+,*ar4+,b
	mac    *ar3+,*ar4+,b
	ld     0x69,b
	add    *ar5,b
	stl    b,*ar5
	ldm    ar1,b
	sub    *ar5,b
	stlm   b,ar3
	stlm   b,ar4
	sth    a,0x6a
	sub    0x6a,16,a
	stl    a,-1,0x6b
	mpy    *ar3+,*ar4+,a
	rpt    #76
	mac    *ar3+,*ar4+,a
	calld  0xe54b
	mac    *ar3+,*ar4+,a
	mac    *ar3+,*ar4+,a
	sfta   a,1
	stm    #106,ar3
	stm    #108,ar4
	sth    a,*ar4
	sub    *ar4+,16,a
	sth    a,15,*ar4-
	mpy    *ar3,*ar4+,b
	mpy    *ar3+,*ar4-,a
	maca   0x6f,b
	mpy    *ar3,*ar4,a
	maca   0x6f,b
	ld     0x68,a
	ld     0x6e,asm
	retd
	ld     b,asm
	sfta   b,15
