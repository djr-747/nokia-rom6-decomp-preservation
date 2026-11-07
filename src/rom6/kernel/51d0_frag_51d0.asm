; ROM6 0x51D0 FRAG_51D0 -- 8w, symbols.yaml data_word.
; Evidence: Bound 51D0-51D7 (8w; exit RET FC00@51D7 byte-verified); head 10F8 0374; entries bc F830@5176->51D4 + F84D@517F->51D4 (from ROUTINE_516A span) + sibling B@51AB->51D4 (from FRAG_5190
; ORIGIN 0x51D0
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x374),a
	bc     0x51cc,aeq
	orm    #256,*ar4
	ld     *ar4,b
	ret
