; ROM6 0x9ED0 WRAP_9ED0 -- 58w, symbols.yaml data_word.
; Evidence: Entry F074 06C0 61F8 085D 0020 F820 9F0A; callers F074@9DDA(in-stub)/9E9E; first-RET @0x9F09 (58w); HYPOTHESIS.
; ORIGIN 0x9ED0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6c0
	bitf   *(0x85d),#32
	bc     0x9f0a,ntc
	stm    #1,ar0
	stm    #200,bk
	mvdm   0x57d,ar2
	stm    #2342,ar3
	mar    *ar2+%
	ld     #159,b
	bitf   *(0x860),#2
	bc     0x9ee9,ntc
	ld     #79,b
	b      0x9eef
	bitf   *(0x860),#144
	bc     0x9eef,ntc
	ld     #16,b
	rpt    *(0xb)
	mvdd   *ar3+,*ar2+0%
	bitf   *(0x861),#1
	stm    #2159,ar2
	st     #2,*ar2
	xc     2,ntc
	orm    #2,*(0x861)
	andm   #-2,*(0x861)
	addm   #1,*(0x57c)
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	ret
