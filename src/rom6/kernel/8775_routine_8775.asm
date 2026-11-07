; ROM6 0x8775 ROUTINE_8775 -- 8w, symbols.yaml data_word.
; Evidence: Bound 8775-877C (8w; exit RET FC00@877C byte-verified, exit scan clean); entries 3x calld F274@ 8761/8766/876B->8775 byte-verified (call-only entry, pre-word F7B8 not post-RET); he
; Pool: ROR/ROL rotates (oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x8775
	.sect ".text"
	.mmregs
	.global _start
_start:
	rptb   0x877b
	ror    a
	ld     #6,b
	nop
	xc     1,c
	xor    b,a
	ret
