; ROM6 0xDA32 FRAG_DA32 -- 3w, symbols.yaml data_word.
; Evidence: Bound DA32-DA34 (3w; exit retd FE00@DA32 + delays DA33-DA34 (765D 6958) included per convention; micro-span, retd-headed); entry bc F845@DA29->DA32 byte-verified (gap-sibling span 
; ORIGIN 0xDA32
	.sect ".text"
	.mmregs
	.global _start
_start:
	retd
	st     #16,0x5a
