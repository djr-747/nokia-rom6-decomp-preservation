; ROM6 0x863A FRAG_863A -- 7w, symbols.yaml data_word.
; Evidence: Bound 863A-8640 (7w; NO own unconditional exit: DSP add-lane (7x adds) runs into MSG_BUILDER_8641 head — tail-frag abut, not a routine); entry = post-RET head (RET@8639 = SUB_8627 
; ORIGIN 0x863A
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    0x40,a
	add    0x20,a
	add    0x18,a
	add    0x0c,a
	add    0x08,a
	add    0x04,a
	add    0x04,a
