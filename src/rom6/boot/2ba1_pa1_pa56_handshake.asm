; ROM6 0x2BA1 PA1_PA56_HANDSHAKE -- 1w, symbols.yaml program_word.
; Evidence: Post-FRETE neighbor of 0x2B53 and frame-cascade target (bit 14). PORTW pa1 sequences, PORTR pa56 poll, B 0x283D gate. Boundary open past the 0x3490 read.
; Pool: 1-word head (st #16384,*ar2 with entry AR2); continuation 0x2BA2 unowned -- revisit in the overlap pass. stays .asm, bytes verified.
; ORIGIN 0x2BA1
	.sect ".text"
	.global _start
_start:
	st     #16384,*ar2
