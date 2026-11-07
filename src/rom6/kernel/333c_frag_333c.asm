; ROM6 0x333C FRAG_333C -- 36w, symbols.yaml data_word.
; Evidence: Bound 333C-335F (36w; exit B F073@335E->2E64 + operand 335F, byte-verified; exit scan clean); entry bc F820@3316->333C byte-verified (cond ntc, thin dark-src from unclaimed arm 330
; Wave-13: second-exit lane @3360-3363 annexed (gap orphan; orm + ret).
; ORIGIN 0x333C
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar2,#16384
	andm   #-7169,*(0x263a)
	bc     0x3346,ntc
	orm    #6144,*(0x263a)
	ld     *ar2,-8,a
	and    #63,a
	ld     *ar2+%,b
	and    #63,b
	stm    #949,ar4
	stl    a,*(0x2655)
	stl    b,*ar4+
	rpt    #30
	mvdd   *ar2+0%,*ar4+
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	call   0x2e2f
	b      0x2e64
	orm    #2,*(0x54f)
	ret
