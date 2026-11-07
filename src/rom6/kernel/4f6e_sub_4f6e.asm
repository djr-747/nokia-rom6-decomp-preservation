; ROM6 0x4F6E SUB_4F6E -- 84w, symbols.yaml data_word.
; Evidence: Entry F074 059C; bound 4F6E-4FC1 (FC00@4FC1); 3x F274 callers @4C1D (objdump calld) + @4CAE/@4D64 (byte-verified F274 4F6E); banzd/rptb-ror leaf, interior b@4F89->4F96; HYPOTHESIS.
; Pool: ROR rotate + ADDC carry + BANZD loop (rotate/carry oracle-unbound; same class as the 436C note); stays .asm, bytes verified.
; ORIGIN 0x4F6E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #1111,ar2
	stm    #12063,ar4
	stm    #0,ar7
	ld     #0,b
	andm   #255,*(0x473)
	stm    #28,ar1
	stm    #456,ar0
	cmpm   *ar4,#192
	bc     0x4f8b,ntc
	stm    #13,ar1
	stm    #211,ar0
	andm   #7,*(0x464)
	b      0x4f96
	cmpm   *ar4,#193
	bc     0x4f96,ntc
	stm    #23,ar1
	stm    #378,ar0
	andm   #1023,*(0x46e)
	ldu    *ar2+,a
	xor    *ar3+,a
	bc     0x4fa1,aeq
	stm    #15,brc
	rptb   0x4fa0
	ror    a
	addc   *(0x17),b
	banz   0x4f96,*ar1-
	stlm   b,ar7
	cmpm   *ar4,#112
	stm    #0,ar2
	xc     2,tc
	stm    #1,ar2
	ld     *(0x2628),b
	and    #16,b
	cmpm   *ar4,#177
	stm    #9340,ar4
	xc     2,bneq
	stm    #1,ar2
	xc     2,tc
	stm    #0,ar2
	ldm    ar7,a
	add    *ar4,a
	stl    a,*ar4+
	ldm    ar0,a
	banzd  0x4fb9,*ar2-
	add    *ar4,a
	stl    a,*ar4+
	ret
