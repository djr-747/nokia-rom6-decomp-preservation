; ROM6 0x9613 BD_LANE_9613 -- 73w, symbols.yaml program_word.
; Evidence: Fall-through from 9609 frag (prev span); stl/addm counter lane, sub/bc select, addm/st preset, bd with mvmd delay into 9667 (cross-span abut); 9629-965B dead past unconditional bd (no entries: bcd/xor/bitf lanes preserved, not modeled); no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x9613
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar4+%
	addm   #-2,*(0x20fd)
	ld     #5,a
	ld     *(0x20fd),b
	sub    #1,b
	bc     0x9625,bgeq
	addm   #1,*(0x20fe)
	ld     #2,a
	st     #0,*(0x20fd)
	bd     0x9667
	mvmd   ar4,0x21fa
	ld     *(0x548),8,b
	and    #-256,b
	stl    b,*(0x548)
	ld     a,-8,b
	and    #255,b
	or     *(0x548),b
	stl    b,*(0x548)
	ld     *(0x20fe),b
	sub    #496,b
	bcd    0x965c,bgt
	orm    #128,*ar2
	addm   #1,*(0x20fe)
	bitf   *(0x20ff),#512
	bc     0x964e,ntc
	xor    #49408,a,b
	bc     0x964e,bneq
	orm    #32,*(0x20ff)
	bitf   *(0x20ff),#16384
	xorm   #16384,*(0x20ff)
	bc     0x965f,tc
	and    #-256,a,b
	bd     0x9667
	stl    b,*ar4
	ld     #6,a
