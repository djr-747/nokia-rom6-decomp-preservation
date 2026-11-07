; ROM6 0x9D16 FRAG_9D16 -- 23w, symbols.yaml data_word.
; Evidence: Bound 9D16-9D2C (23w; exit retd FE00@9D2A + delays F2C4/1C86 9D2B-9D2C included per convention; exit scan clean); post-RET head only (FC00@9D15, zero exterior refs — thin entry, no
; ORIGIN 0x9D16
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-19437,ar6
	xc     1,aleq
	mar    *ar6+
	abs    a
	exp    a
	pshm   al
	ldm    t,b
	xc     1,aneq
	ld     #23,a
	min    b
	sub    a,b
	stlm   b,t
	popm   al
	neg    b
	norm   a
	sfta   a,-3
	xc     2,beq
	sfta   a,-1
	ld     #1,b
	retd
	xor    b,4,a
	xor    *ar6,a
