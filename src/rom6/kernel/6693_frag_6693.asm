; ROM6 0x6693 FRAG_6693 -- 20w, symbols.yaml data_word.
; Evidence: Bound 6693-66A6 (20w; exit B F073@66A5->66CB + operand 66A6, byte-verified (66CB = FRAG_66CB head, CODE); exit scan clean); entry bc F820@667C->6693 byte-verified (cond ntc, exteri
; ORIGIN 0x6693
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0xb),#4
	bc     0x66e2,ntc
	stm    #12251,ar1
	bitf   *(0x51e),#8
	bc     0x66ac,tc
	ld     *ar1,a
	sub    #14,a
	bc     0x66a7,alt
	ld     #0,b
	b      0x66cb
