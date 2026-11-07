; ROM6 0x43D3 FRAG_43D3 -- 23w, symbols.yaml data_word.
; Evidence: Bound 43D3-43E9 (23w; exit RET FC00@43E9 byte-verified, exit scan clean); post-RET head (FC00@43D2, zero exterior refs — thin entry); interior F072@43D7->43DA (rptb) + out-call F07
; ORIGIN 0x43D3
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #12033,ar4
	stm    #1,brc
	rptb   0x43da
	ld     *ar2+%,a
	stl    a,*ar4+
	call   0x2e2f
	and    #255,a
	sub    #1,a
	bc     0x4533,aeq
	stm    #1319,ar3
	stm    #12032,ar4
	rpt    #2
	mvdd   *ar4+,*ar3+
	ret
