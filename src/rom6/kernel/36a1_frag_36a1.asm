; ROM6 0x36A1 FRAG_36A1 -- 15w, symbols.yaml data_word.
; Evidence: Bound 36A1-36AF (15w; NO exit-class in-span — falls into FRAG_36B0 head, no-exit micro abut per 6753 precedent; pre-word 2E64 = dispatch value, not post-RET — entry is branch-based
; ORIGIN 0x36A1
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x58f),#128
	bc     0x36b0,tc
	bitf   *(0x250f),#208
	bc     0x36c2,tc
	bitf   *(0x250f),#32
	bc     0x36c2,ntc
