; ROM6 0x576E FRAG_576E -- 53w, symbols.yaml data_word.
; Evidence: Bound 576E-57A2 (53w; exit RET FC00@57A2 byte-verified, exit scan clean); entries sibling-only bc F844@5760->576E + F820@576B->5785 mid-span (from ROUTINE_5755 interior, chained ed
; ORIGIN 0x576E
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x250f),b
	sub    #81,b,a
	bc     0x5778,aeq
	sub    #80,b,a
	bc     0x577e,aneq
	cmpm   *(0x915),#2
	rc     ntc
	b      0x5785
	sub    #82,b,a
	rc     aneq
	cmpm   *(0x91b),#159
	rc     ntc
	ld     *(0x250f),b
	and    #240,b
	stm    #9311,ar1
	ld     *ar1,a
	addm   #1,*ar1
	rc     aleq
	sub    #80,b,a
	bc     0x579d,aeq
	sub    #16,b,a
	rc     aneq
	ld     *ar1,a
	add    *(0x250c),a
	stl    a,*ar1
	sub    *(0x2654),a
	rc     aleq
	st     #1,*ar1
	orm    #64,*(0x2628)
	ret
