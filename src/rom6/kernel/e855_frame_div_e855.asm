; ROM6 0xE855 FRAME_DIV_E855 -- 24w (dark-gap pool).
; Evidence: Fall-through from e837 blk (prev span); frame-based 16-step subc divide with mpy correction and dual stl store, frame teardown, fbacc return; frame/fbacc have no C form (pool); next span e86d owns the fbacc landing region.
; ORIGIN 0xE855
	.sect ".text"
	.mmregs
	.global _start
_start:
	frame  -1
	ld     *(0x3e21),a
	mvkd   0x2d31,0x00
	rpt    #15
	subc   0x00,a
	and    #-1,a
	ld     *(0x3e23),b
	sub    a,b
	stlm   b,t
	mpy    #19661,b
	add    b,-16,a
	stl    a,*(0x3e24)
	stl    a,*(0x3e24)
	frame  1
	popm   ah
	popm   al
	fbacc  a
