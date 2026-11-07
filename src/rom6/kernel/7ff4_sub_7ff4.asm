; ROM6 0x7FF4 SUB_7FF4 -- 57w, symbols.yaml data_word.
; Evidence: Entry F074 059E 10F8 2650 F844 805A; zero callers (bc @7C8A NOT counted); interior uncond b 802B->802F; shrunk bound 7FF4-802C incl operand (linear ret 807E abuts 807F); HYPOTHESIS
; ORIGIN 0x7FF4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	ld     *(0x2650),a
	bc     0x805a,aneq
	ld     *(0x25d6),a
	bc     0x8009,aneq
	ld     #6,b
	call   0x4590
	stm    #9688,ar4
	rpt    #3
	mvkd   0xb1cd,*ar4+
	rptz   b,#6
	stl    b,*ar4+
	stm    #9686,ar4
	st     #0,*ar4+
	ld     *(0x2645),b
	sfta   b,8
	cmpm   *(0x250f),#34
	bc     0x8029,ntc
	cmpm   *(0x34bf),#3
	bc     0x801f,ntc
	bitf   *(0x3490),#1
	bc     0x802d,tc
	cmpm   *(0x34bf),#1
	bc     0x802d,tc
	cmpm   *(0x34bf),#4
	bc     0x802d,tc
	or     *(0x2644),b
	b      0x802f
