; ROM6 0x351D FRAG_351D -- 27w, symbols.yaml data_word.
; Evidence: Bound 351D-3537 (exit F073@3536->2E64 + operand 3537, byte-verified single F073 in span); post-RET head (after ROUTINE_3500 RET@351C); zero callers/branch-refs; interior 4x F074->2
; ORIGIN 0x351D
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar4,b
	add    #1,b,a
	sfta   a,-1
	sub    #1,a
	bc     0x352a,alt
	stm    #12032,ar3
	rpt    *(0x8)
	mvdd   *ar2+0%,*ar3+
	call   0x2e2f
	bitf   *(0x20ff),#1536
	stm    #248,ar0
	ld     #28,a
	ccd    0x93ce,ntc
	stm    #12032,ar2
	b      0x2e64
