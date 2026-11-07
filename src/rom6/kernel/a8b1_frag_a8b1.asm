; ROM6 0xA8B1 FRAG_A8B1 -- 8w, symbols.yaml data_word.
; Evidence: Bound A8B1-A8B8 (8w; NO exit-class in-span — falls into FRAG_A8B9 head, no-exit micro abut per 6753 precedent; pre-word FC00 = FRAG_A8A5 exit, post-RET rule applies but entry is br
; ORIGIN 0xA8B1
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x51c),a
	and    #1,a
	rc     aeq
	ld     *(0x3082),a
	rc     aeq
