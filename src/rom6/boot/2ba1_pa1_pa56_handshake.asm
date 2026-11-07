; ROM6 0x2BA1 PA1_PA56_HANDSHAKE -- 1w, symbols.yaml program_word.
; Evidence: Post-FRETE neighbor of 0x2B53 and frame-cascade target (bit 14). PORTW pa1 sequences, PORTR pa56 poll, B 0x283D gate. Boundary open past the 0x3490 read.
; Pool: 1-word head (st #16384,*ar2 with entry AR2); continuation 0x2BA2 unowned -- revisit in the overlap pass. stays .asm, bytes verified.
; Bound 2BA1-2BA9 (st; nop; portw pa1; rpt #13 nop; b 0x283D gate). Former 1w head extended wave-13 (gap 2BA3-2BA9 owned; 2BA2 continuation resolved here).
; ORIGIN 0x2BA1
	.sect ".text"
	.global _start
_start:
	st     #16384,*ar2
	nop
	portw  *ar2,1
	rpt    #13
	nop
	b      0x283d
