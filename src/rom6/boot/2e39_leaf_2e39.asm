; ROM6 0x2E39 LEAF_2E39 -- 25w, symbols.yaml data_word.
; Evidence: Entry 61F8 0549 0020 F820 (bitf *(0x549)#32; bc); bound 2E39-2E51 (25w, FC00@2E51); 4x ext callers F074->2E39 @211A/21FC/2237/227D (byte+objdump verified); post-ret boundary (FC00@
; ORIGIN 0x2E39
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x549),#32
	bc     0x2e4a,ntc
	pshm   ar2
	stm    #1353,ar3
	andm   #-33,*ar3
	stm    #159,ar4
	stm    #2,ar5
	call   0x2c88
	popm   ar2
	bitf   *(0x54d),#4
	bc     0x2e52,ntc
	call   0x2e64
	ret
