; ROM6 0x9AF4 FRAG_9AF4 -- 8w, symbols.yaml data_word.
; Evidence: Bound 9AF4-9AFB (8w; exit retd FE00@9AF9 + delays 9AFA-9AFB (words F010 001E — suspicious non-NOP delay content, flagged, still architectural delays) included per convention; micro
; ORIGIN 0x9AF4
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #-1,*(0x20fa)
	ld     *(0x20fe),a
	retd
	sub    #30,a
