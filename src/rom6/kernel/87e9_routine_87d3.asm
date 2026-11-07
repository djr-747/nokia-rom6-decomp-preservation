; ROM6 0x87E9 ROUTINE_87D3 -- 2w, symbols.yaml data_word.
; Evidence: Bound 87D3-87E8 (22w; TRIMMED from 87D3-8820 draft at first-outside retd FE00@87E8 — retd is an exit per convention, ordered-scan rule; Bound 87E9-87EA (RETD@87E8 delay slots — wav
; Pool: NORM exponent op + 3-operand SUB (oracle-unbound); stays .asm, bytes verified.
; Pool: NORM single-step (exponent op, oracle-unbound) + 3-operand SUB; stays .asm, bytes verified.
; ORIGIN 0x87E9
	.sect ".text"
	.mmregs
	.global _start
_start:
	norm   a
	sub    b,3,a
