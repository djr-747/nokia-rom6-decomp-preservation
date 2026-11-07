; ROM6 0x6657 FRAG_6657 -- 15w, symbols.yaml data_word.
; Evidence: Bound 6657-6665 (15w; NO exit-class in-span — FC00-free, falls into FRAG_6666 head, no-exit tail abut per 6753/810A precedent; pre-word 6666 = next-head value, not post-RET — entry
; ORIGIN 0x6657
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #204,a
	calld  0x6976
	stm    #12249,ar2
	add    #51,b,a
	sub    #204,a
	nop
	nop
	xc     2,alt
	add    #204,a
	min    b
