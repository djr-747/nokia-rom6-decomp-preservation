; ROM6 0x49F7 FRAG_49F7 -- 10w, symbols.yaml data_word.
; Evidence: Bound 49F7-4A00 (10w; exit F073@49FF->4A07 + operand 4A00, byte-verified); entry bc F820@49EB-> 49F7 byte-verified (cond); abuts FRAG_49B6 (ends 49F6); B-lane chain link; HYPOTHESI
; ORIGIN 0x49F7
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x37b0),#15
	bc     0x4a4b,ntc
	st     #0,*(0x37b0)
	b      0x4a4b
