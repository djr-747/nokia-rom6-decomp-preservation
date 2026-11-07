; ROM6 0x57A3 SUB_57A3 -- 41w head lane, abuts FRAG_57CC.
; Evidence: Entry F074 059C 10F8 250F F030 FFFE 60F8 0008 0020 F820 57D3; caller F074@5209 objdump-verified (call 0x57a3); head bound 57A3-57CB (41w, exit fall-through abut into 57CC; in-head exits bc F820@57AC->57D3 + bd F273@57C8->57F4 + bc F845@57BC->57EE + bc F845@57C5->57F2); whole-routine first RET FC00@57FD lives in the 57CC tail span (separate module, recombine MATCH); HYPOTHESIS.
; ORIGIN 0x57A3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	ld     *(0x250f),a
	and    #-2,a
	cmpm   *(0x8),#32
	bc     0x57d3,ntc
	ld     *(0x918),a
	sub    #52,a,b
	cmpm   *(0x250f),#33
	xc     1,bgeq
	ld     b,a
	xc     2,tc
	sub    #14,a
	ld     *(0x2628),b
	bc     0x57ee,aeq
	rc     alt
	sub    #6,a
	bc     0x57cc,aeq
	sub    #1,a
	bc     0x57f2,aeq
	rc     agt
	bd     0x57f4
	or     #4,b
