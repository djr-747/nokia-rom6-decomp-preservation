; ROM6 0xC7F6 FRAG_C7F6 -- 16w, symbols.yaml data_word.
; Evidence: Bound C7F6-C805 (16w; exit B F073@C804->283D + operand C805, byte-verified (283D hub, CODE); exit scan clean); entry B F073@C7D0->C7F6 byte-verified (exterior from FRAG_C7B1 [C7B1-
; Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded); stays .asm, bytes verified.
; ORIGIN 0xC7F6
	.sect ".text"
	.mmregs
	.global _start
_start:
	nop
	stl    a,*ar4+%
	ld     *ar5,a
	and    #255,a
	sub    *ar7,a
	addm   #1,*ar7
	bcd    0x283d,agt
	mvmd   ar4,0x54a
	st     #0,*ar7
	b      0x283d
