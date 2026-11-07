; ROM6 0x9C4D WRAP_9C4D -- 20w, symbols.yaml data_word.
; Evidence: Entry 7312 21FB 4914 68F8 20FF 7FFF; bound 9C4D-9C60 (FC00@9C60); callers F074 @9BBC/9BC9/9C21 (objdump-verified); interior bc@9C58 beq; zero interior calls; HYPOTHESIS small flag-
; ORIGIN 0x9C4D
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmd   ar2,0x21fb
	ldm    ar4,b
	andm   #32767,*(0x20ff)
	bc     0x9c58,beq
	orm    #-32768,*(0x20ff)
	ssbx   st1,intm
	ldm    ar6,b
	neg    b
	add    *(0x20fe),b
	stl    b,*(0x20fe)
	rsbx   st1,intm
	ret
