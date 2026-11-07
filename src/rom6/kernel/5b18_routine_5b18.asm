; ROM6 0x5B18 ROUTINE_5B18 -- 14w, symbols.yaml data_word.
; Evidence: Bound 5B18-5B25 (14w; exit RET FC00@5B25 byte-verified, exit scan clean); entries 4x calld F274@ 4BE0/4C4C/4CDD/4CF9->5B18 byte-verified + post-RET head (FC00@5B17 = FRAG_5AFB exit
; ORIGIN 0x5B18
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5fc
	stm    #3,brc
	ld     *ar3+,a
	rptb   0x5b22
	and    #15,a,b
	stl    b,*ar2+
	ld     a,-4,a
	banz   0x5b1a,*ar1-
	ret
