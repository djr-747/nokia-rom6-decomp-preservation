; ROM6 0xA4BA ROUTINE_A4BA -- 27w, symbols.yaml data_word.
; Evidence: Bound A4BA-A4D4 (27w; exit RET FC00@A4D4 byte-verified, exit scan clean); entries call F074@B3A6-> A4BA byte-verified (caller sits in ROUTINE_B39E draft span — sibling edge, flagge
; ORIGIN 0xA4BA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x656
	stm    #9771,ar2
	ld     *ar2,a
	rc     aeq
	sub    #240,a
	rc     aeq
	bitf   *(0x263a),#512
	bc     0xa4cb,ntc
	orm    #256,*(0x51e)
	ld     *(0x2639),b
	and    #2,b
	andm   #-3,*(0x2639)
	call   0x7c57
	ret
