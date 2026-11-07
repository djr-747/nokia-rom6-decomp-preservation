; ROM6 0x5AFB FRAG_5AFB -- 29w, symbols.yaml data_word.
; Evidence: Bound 5AFB-5B17 (29w; exit RET FC00@5B17 byte-verified, exit scan clean); entries bc F820@5AF5-> 5AFB byte-verified (exterior, SEG_5AC8) + B F073@5AF9->5AFD mid-span; interior join
; ORIGIN 0x5AFB
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #11036,a
	and    #-1,a
	sub    #627,a
	bc     0x5b05,ageq
	add    #627,a
	cmpm   *(0x250f),#34
	bc     0x5b0e,ntc
	add    *(0x352c),a
	b      0x5b10
	add    #11036,a
	stlm   a,ar3
	banz   0x5ad4,*ar6-
	ld     #12,b
	stlm   b,t
	banz   0x5ad2,*ar1-
	ret
