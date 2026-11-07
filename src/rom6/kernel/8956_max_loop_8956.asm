; ROM6 0x8956 MAX_LOOP_8956 -- 93w, symbols.yaml program_word.
; Evidence: Fall-through from 8936 frag (prev span); bitf/bcd flag lane, stm/ld/sub/bgeq B-select, add/ld lane, rptb max-fold (RPTBD RSA+4 flagged), stm/rpt/mvdk fill, mvdd +0% lane, dark 89C4 call, b-tail into prev 88AD region; bd-lane delay abut; 8990-89B2 dead past unconditional bd (no entries); exterior callers none, entry unconfirmed, flagged.
; ORIGIN 0x8956
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar4,#1
	bcd    0x8976,ntc
	orm    #1,*ar4
	andm   #-7,*ar4
	orm    #4,*ar4
	stm    #1370,ar2
	ld     *ar2,a
	sub    #5,a,b
	bc     0x89b3,bgeq
	add    #1,a
	stl    a,*ar2
	ld     #0,a
	stm    #3,brc
	rptbd  0x8975
	stm    #4516,ar2
	ld     *ar2,b
	sub    #11,b
	max    b
	stl    b,*ar2+
	stm    #4508,ar2
	rpt    #7
	mvdk   *ar2+,0x3090
	stm    #12443,ar3
	stm    #17,ar0
	rpt    #3
	mvdd   *ar2+,*ar3+0%
	call   0x89c4
	b      0x88ad
	st     #0,*(0x55a)
	andm   #-2,*ar4
	andm   #-7,*ar4
	bd     0x8976
	orm    #2,*ar4
	st     #0,*(0x55a)
	andm   #-2,*ar4
	stm    #2504,ar4
	calld  0x86fb
	stm    #12432,ar3
	stm    #4508,ar3
	rpt    #7
	.word 0x7093 ; mvdk 0x3090,*ar3+ (gas dmad cannot emit direct-src/indirect-dst; hand-encoded per 64A0)
	.word 0x3090
	stm    #3,brc
	stm    #12443,ar2
	ld     *ar2,b
	rptbd  0x89ae
	stm    #17,ar0
	add    *ar3,b,a
	stl    b,*ar3+
	stl    a,-1,*ar2+0
	ld     *ar2,b
	call   0x89c4
	b      0x88ad
