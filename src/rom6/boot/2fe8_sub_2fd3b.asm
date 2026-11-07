; ROM6 0x2FE8 SUB_2FD3B -- 58w, symbols.yaml program_word.
; Evidence: Bound 2FE8-3021 (58w); entry TRACE (same histogram: 2FE8 bc-taken lane x1, 2FF2 b-target x1, hot 2FFF-3001 lane x4); interior bc lanes; exits b F073@3020->2E64; tail 3022-3027 (inc
; ORIGIN 0x2FE8
	.sect ".text"
	.mmregs
	.global _start
_start:
	andm   #-513,*(0x2549)
	and    #1,a,b
	bc     0x2ff2,bneq
	andm   #-513,*(0x2512)
	stm    #9547,ar4
	mvmm   ar4,ar5
	and    #1,a,b
	bc     0x2ffb,bneq
	stm    #9492,ar5
	stm    #3,brc
	rptb   0x3001
	ld     *ar2+%,b
	stl    b,*ar4+
	stl    b,*ar5+
	stm    #0,ar4
	bitf   *(0x13),#1
	bc     0x300b,ntc
	stm    #1,ar4
	mvmd   ar4,0x56d
	and    #1,a
	bc     0x301e,aneq
	portr  56,*(0x8)
	or     #16,a
	banz   0x301a,*ar4
	and    #-17,a
	nop
	portw  *(0x8),56
	call   0x2e2f
	b      0x2e64
