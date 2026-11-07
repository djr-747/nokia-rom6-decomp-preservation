; ROM6 0x4A12 FRAG_4A12 -- 7w, symbols.yaml data_word.
; Evidence: Bound 4A12-4A18 (7w; exit F073@4A17->4A12 + operand 4A18 — self-loop exit to own head, byte- verified); entries 2x bc F830@4A04/4A09->4A12 byte-verified (cond pair); abuts FRAG_4A0
; ORIGIN 0x4A12
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x37b0),#15
	bc     0x4a1e,tc
	b      0x4a4b
