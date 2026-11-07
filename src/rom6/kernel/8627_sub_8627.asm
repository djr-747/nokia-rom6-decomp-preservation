; ROM6 0x8627 SUB_8627 -- 19w, symbols.yaml data_word.
; Evidence: Entry 4593 F793 771A 000F F072 8636 (rptb 0x8636 loop, banz self @8637); caller F074 @8622 verified; first exit ret @8639; bound 8627-8639; HYPOTHESIS.
; Pool: ROL rotates + self-BANZ loop (rotate family oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x8627
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar3+,16,b
	cmpl   b
	stm    #15,brc
	rptb   0x8636
	rol    b
	rol    a
	nop
	nop
	xc     2,c
	xor    #8265,16,a
	xc     2,c
	xor    #32405,a
	banz   0x8627,*ar2-
	ret
