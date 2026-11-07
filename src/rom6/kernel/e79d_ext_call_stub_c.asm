; ROM6 0xE79D EXT_CALL_STUB_C -- 82w, symbols.yaml data_word.
; Evidence: Entry F074 05B0 61F8 051D 0100 F820 E7A7; 76F8 mem-fill lane; first-RET @E7EE (82w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE79D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b0
	bitf   *(0x51d),#256
	bc     0xe7a7,ntc
	st     #0,*(0x50e)
	st     #10240,*(0x296a)
	st     #10240,*(0x296c)
	st     #10240,*(0x296d)
	st     #10240,*(0x296b)
	st     #0,*(0x2969)
	st     #0,*(0x2978)
	st     #2,*(0x2966)
	st     #0,*(0x2967)
	st     #0,*(0x2968)
	st     #0,*(0x2977)
	andm   #-4969,*(0x537)
	st     #0,*(0x2453)
	bitf   *(0x51d),#256
	bc     0xe7de,ntc
	andm   #-33,*(0x54f)
	andm   #-257,*(0x51d)
	orm    #2,*(0x2453)
	st     #0,*(0x50b)
	b      0xe7ee
	stm    #1310,ar3
	bitf   *(0x54f),#8
	andm   #-16385,*ar3
	xc     2,tc
	orm    #16384,*ar3
	andm   #-9,*(0x54f)
	andm   #-9,*(0x51e)
	ret
