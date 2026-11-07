; ROM6 0x29D3 FRAG_29D3 -- 14w, symbols.yaml data_word.
; Evidence: Bound 29D3-29E0 (14w; exit B F073@29DF->2A8A + operand 29E0, byte-verified; exit scan clean); entry bc F820@29BB->29D3 byte-verified (cond ntc, chained from FRAG_29B9 interior); ve
; ORIGIN 0x29D3
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#2048
	bc     0x29e1,ntc
	st     #4,*ar3
	stm    #4726,ar3
	stm    #4720,ar2
	andm   #32767,*ar3
	b      0x2a8a
