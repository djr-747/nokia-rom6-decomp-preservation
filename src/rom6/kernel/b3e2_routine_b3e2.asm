; ROM6 0xB3E2 ROUTINE_B3E2 -- 58w, symbols.yaml data_word.
; Evidence: Bound B3E2-B41B (58w; exit RET FC00@B41B objdump-aligned, next word SUB_B41C head, no overlap); entries 5x F074 call word-verified B1B0/B1F7/B25D/B2D0/B312; bytes F074 05A8 7712 34
; ORIGIN 0xB3E2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a8
	stm    #13456,ar2
	ld     *ar2,a
	and    #-16,a
	or     #8,a
	stl    a,*ar2
	st     #9831,*(0x348f)
	mvdk   *(0x2639),0x34c9
	call   0xb41c
	ld     *(0x34bf),a
	rc     aeq
	stm    #13456,ar2
	ld     *ar2,a
	and    #-16,a
	or     #1,a
	stl    a,*ar2
	st     #10143,*(0x348f)
	mvdk   *(0x34c9),0x2639
	call   0xb41c
	cmpm   *(0x34bf),#4
	rc     ntc
	stm    #13456,ar2
	ld     *ar2,a
	and    #-16,a
	or     #2,a
	stl    a,*ar2
	st     #10455,*(0x348f)
	mvdk   *(0x34c9),0x2639
	call   0xb41c
	ret
