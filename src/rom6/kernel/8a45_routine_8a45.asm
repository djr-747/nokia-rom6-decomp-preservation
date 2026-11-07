; ROM6 0x8A45 ROUTINE_8A45 -- 15w, symbols.yaml data_word.
; Evidence: Bound 8A45-8A53 (15w; exit RET FC00@8A53 byte-verified, exit scan clean); entries call F074@8650-> 8A45 byte-verified (from MSG_BUILDER_864E) + post-RET at 8A43 (retd delays of ROU
; ORIGIN 0x8A45
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	stm    #4352,ar2
	rptz   a,#8
	stl    a,*ar2+
	stm    #128,brc
	rptbd  0x8a52
	st     #40,*ar2+
	stl    a,*ar2+
	ret
