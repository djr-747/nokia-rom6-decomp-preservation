; ROM6 0x8894 FRAG_8894 -- 37w, symbols.yaml data_word.
; Evidence: Bound 8894-88B8 (FC00@88B8); entry F073@89C2 (objdump b->8894); interior calld 86E3@8897, rptbd@88B1->88B7, join F073@8892->889B; tail 889B-88B8 shared (rptbd/or/STL+RET); HYPOTHES
; ORIGIN 0x8894
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	stm    #12432,ar3
	calld  0x86e3
	stm    #4491,ar4
	stm    #0,bk
	stm    #17,ar0
	stm    #12082,ar4
	stm    #12441,ar2
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	stm    #12442,ar2
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	stm    #12443,ar2
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	stm    #4508,ar2
	stm    #11,brc
	rptbd  0x88b7
	stm    #12082,ar3
	ld     *ar3+,8,a
	or     *ar2,a
	stl    a,*ar2+
	ret
