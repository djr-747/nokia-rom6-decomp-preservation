; ROM6 0x397B FRAG_397B -- 11w, symbols.yaml data_word.
; Evidence: Bound 397B-3985 (11w; exit RET FC00@3985 byte-verified, exit scan clean); entries bc F820@396D-> 397B byte-verified (from FRAG_3938 [3938-397A] interior) + post-RET head (FC00@397A
; ORIGIN 0x397B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	stl    a,*ar2+
	sth    a,*ar2+
	stm    #16080,ar3
	xc     2,bneq
	stm    #16001,ar3
	mvdd   *ar3+,*ar2+
	mvdd   *ar3+,*ar2+
	ret
