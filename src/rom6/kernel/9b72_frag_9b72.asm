; ROM6 0x9B72 FRAG_9B72 -- 81w, symbols.yaml data_word.
; Evidence: Bound 9B72-9BC2 (81w; exit RET FC00@9BC2 byte-verified; interior BD-join F273@9B86->9B8F; exit scan otherwise clean); post-RET head (FE00@9B71, retd pre-word — valid post-RET rule)
; ORIGIN 0x9B72
	.sect ".text"
	.mmregs
	.global _start
_start:
	and    #255,b
	frame  1
	stm    #0,ar6
	ld     *(0x20ff),a
	and    #-32768,a
	mvmm   ar6,ar4
	mvmm   ar6,ar0
	mvmm   ar6,ar7
	xc     1,aneq
	mar    *ar4+
	banz   0x9b8a,*ar4
	ld     *ar2,-8,b
	mar    *ar4+
	mar    *ar6+
	bd     0x9b8f
	and    #255,b
	ld     *ar2+%,b
	mar    *ar4-
	mar    *ar6+
	and    #255,b
	sub    #192,b,a
	bc     0x9ba5,aneq
	mar    *ar0+
	banz   0x9b97,*ar4
	mar    *ar2-%
	mar    *ar6-
	mvmd   ar2,0x2f00
	mvmd   ar4,0x2f01
	mvmd   ar6,0x2f02
	xorm   #1,*(0x2f01)
	banz   0x9ba4,*ar4
	mar    *ar2+%
	mar    *ar6+
	xor    #193,b
	bc     0x9baa,bneq
	mvmm   ar0,ar7
	ldm    ar6,a
	sub    *(0x20fe),a
	bc     0x9bb2,aeq
	ldm    ar7,a
	bc     0x9b80,aeq
	ldm    ar0,a
	bc     0x9bbc,aeq
	ldm    ar6,a
	sub    *(0x2f02),a
	sub    #256,a
	bc     0x9bc3,alt
	call   0x9c4d
	ld     #-1,a
	stl    a,*(0x20fa)
	ret
