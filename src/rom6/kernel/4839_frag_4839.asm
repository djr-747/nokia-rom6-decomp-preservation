; ROM6 0x4839 FRAG_4839 -- 31w, symbols.yaml data_word.
; Evidence: Bound 4839-4857 (31w, FC00@4857); post-ret head, zero callers/refs image-wide; F074 059E + 2x RPTB/xorm/banz loops; interior F844 bc only; VERIFIES sole-FC00 note (full-range scan 
; Pool: ROR-through-carry (rotate count rides the unbound carry flag -- no oracle form; same class as the 436C/4F5F ROR notes) plus XORM/T-state in the rptb/banz loops; stays .asm, bytes verified.
; ORIGIN 0x4839
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #352,ar2
	stm    #6,ar1
	ld     *ar4+,b
	stm    #15,brc
	rptb   0x4849
	ror    b
	bc     0x4849,nc
	xorm   #15,*ar2
	mar    *ar2+
	banz   0x483f,*ar1-
	ld     *ar4,b
	stm    #1,brc
	rptb   0x4856
	ror    b
	bc     0x4856,nc
	xorm   #15,*ar2
	mar    *ar2+
	ret
