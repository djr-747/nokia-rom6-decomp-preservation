; ROM6 0x4A46 FRAG_4A46 -- 5w, symbols.yaml data_word.
; Evidence: Bound 4A46-4A4A (5w; exit F073@4A49->4A3C + operand 4A4A, byte-verified, back-edge into FRAG_4A19 span); entry bc F820@4A3C->4A46 byte-verified (cond, from FRAG_4A19 interior — cha
; ORIGIN 0x4A46
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #0,*+ar2(0xffff)
	b      0x4adf
