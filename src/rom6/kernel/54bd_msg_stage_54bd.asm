; ROM6 0x54BD MSG_STAGE_54BD -- 59w, symbols.yaml program_word.
; Evidence: Fall-through from 54bb producer-converge (prev span); st/ld/and/sub lane with andm fork, calld-2262 lane, cmpm guard, st/mvkd seed, rpt/mvdd copy, bitf-gated second copy, b-tail into next span 54F8; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x54BD
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #0,*(0x2efd)
	ld     *(0x2547),a
	and    #240,a
	sub    #176,a
	bc     0x54cb,aneq
	andm   #-873,*(0x537)
	stm    #9543,ar2
	ld     *ar2,a
	and    #240,a
	sub    #208,a
	bc     0x54db,aneq
	andm   #-777,*(0x537)
	calld  0x2262
	stm    #6,ar2
	cmpm   *(0x2546),#34
	bc     0x54e6,ntc
	st     #0,*(0x3490)
	mvkd   0x34c0,*(0x34bf)
	stm    #9537,ar2
	stm    #9482,ar3
	rpt    #7
	mvdd   *ar2+,*ar3+
	stm    #9545,ar2
	stm    #9490,ar3
	bitf   *(0x54f),#16
	bc     0x54f8,ntc
	mvdd   *ar2,*ar3
	b      0x5503
