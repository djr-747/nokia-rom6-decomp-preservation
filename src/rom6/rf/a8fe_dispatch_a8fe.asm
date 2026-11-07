; ROM6 0xA8FE DISPATCH_A8FE -- 30w, symbols.yaml data_word.
; Evidence: Entry F074 0666 61F8 051C 0040 F830; bound A8FE-A91B (FC00@A91B); caller F074@A86C (objdump-verified call 0xa8fe); interior calls 0666/BBEF/9FCF/A12B/9F42/06A2/BADB (all verified);
; ORIGIN 0xA8FE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x666
	bitf   *(0x51c),#64
	bc     0xa91b,tc
	calld  0xbbef
	stm    #12694,ar2
	calld  0x9fcf
	stm    #10380,ar6
	call   0xa12b
	calld  0x9f42
	stm    #159,brc
	calld  0x6a2
	stm    #12694,ar2
	calld  0xbadb
	stm    #12694,ar2
	ret
