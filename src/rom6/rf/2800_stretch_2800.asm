; ROM6 0x2800 STRETCH_2800 -- 103w, symbols.yaml data_word.
; Evidence: Entry F84C 2875 (bc bneq; fall-through from 27FE-27FF instruction); bound 2800-2866 (103w, exit FRETE F4E5@2866); WEAK head: possible FRAME_ISR_27CD continuation (no ret verified 2
; ORIGIN 0x2800
	.sect ".text"
	.mmregs
	.global _start
_start:
	bc     0x2875,bneq
	bitf   *(0x20ff),#1024
	bc     0x2811,tc
	and    #256,a,b
	bc     0x952e,bneq
	and    #512,a,b
	bc     0x953c,bneq
	b      0x2819
	and    #256,a,b
	bc     0xc806,bneq
	and    #512,a,b
	bc     0xc7b1,bneq
	and    #1024,a,b
	bc     0x94f0,bneq
	and    #128,a,b
	bc     0x2afc,bneq
	and    #2,a,b
	bc     0x2867,bneq
	and    #1,a,b
	bc     0x2873,bneq
	and    #32,a,b
	bc     0x2b45,bneq
	and    #64,a,b
	bc     0x2b45,bneq
	and    #16384,a,b
	bc     0x2ba1,bneq
	and    #2048,a,b
	bc     0x2baa,bneq
	and    #-32768,a,b
	bc     0x2c03,bneq
	stm    #542,ar2
	portr  2,*ar2
	st     #-1,*(0x8)
	nop
	portw  *(0x8),2
	rpt    #1
	nop
	nop
	portw  *ar2,2
	popm   bk
	popm   rea
	popm   rsa
	popm   brc
	popm   ar7
	popm   ar6
	popm   ar5
	popm   ar4
	popm   ar3
	popm   ar2
	popm   ar1
	popm   ar0
	popm   t
	popd   *(0x61)
	popd   *(0x60)
	popm   bg
	popm   bh
	popm   bl
	popm   ag
	popm   ah
	popm   al
	popm   st1
	popm   st0
	frete
