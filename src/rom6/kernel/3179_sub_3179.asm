; ROM6 0x3179 SUB_3179 -- 28w, symbols.yaml program_word.
; Evidence: Bound 3179-3194 (22w); entry TRACE (same histogram: 3179-3193 heads x2); exits b F073@3193->2E64; tail 3195-3198 (orm/ret) unexecuted, stays dark; HYPOTHESIS.
; Wave-13: second-exit lane @3195-3198 annexed (gap orphan; orm + ret).
; ORIGIN 0x3179
	.sect ".text"
	.global _start
_start:
	stm    #9490,ar4
	ldu    *ar2+%,a
	ld     *ar4,b
	and    #-1025,b
	xc     2,aneq
	or     #1024,b
	stl    b,*ar4
	stm    #9799,ar4
	ldu    *ar2+%,a
	sftl   a,-8,b
	stl    b,*ar4-
	and    #255,a,b
	st     #224,*ar4
	stm    #9790,ar4
	ld     *ar2+%,a
	stl    b,*ar4+
	stl    a,*ar4
	call   0x2e2f
	b      0x2e64
	orm    #256,*(0x2627)
	ret
