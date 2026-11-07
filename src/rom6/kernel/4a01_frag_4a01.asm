; ROM6 0x4A01 FRAG_4A01 -- 17w, symbols.yaml data_word.
; Evidence: Bound 4A01-4A11 (17w; exit F073@4A10->4A21 + operand 4A11, byte-verified); entry bc F820@49E6-> 4A01 byte-verified (cond, backward from pre-lane zone); abuts FRAG_49F7 (ends 4A00);
; ORIGIN 0x4A01
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x34bf),#1
	bc     0x4a12,tc
	cmpm   *(0x34bf),#4
	bc     0x4a12,tc
	cmpm   *(0x366f),#15
	bc     0x4a1e,tc
	b      0x4a4b
