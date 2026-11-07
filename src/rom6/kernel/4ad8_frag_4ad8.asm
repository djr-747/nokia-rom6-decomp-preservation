; ROM6 0x4AD8 FRAG_4AD8 -- 7w, symbols.yaml data_word.
; Evidence: Bound 4AD8-4ADE (7w; NO exit-class in-span — falls into FRAG_4ADF head, no-exit tail abut per 6753 precedent; pre-word 4ADF = next-head RET value, not post-RET — entry is branch-ba
; Pool: CALAD A-reg computed call with delay (oracle-unbound); stays .asm, bytes verified.
; Pool: CALAD A-reg computed call with delay (oracle-unbound); stays .asm, bytes verified.
; Wave-13: exit ret @4ADF owned here (gap orphan annexed).
; ORIGIN 0x4AD8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #19244,a
	mvdk   *ar2,0x12
	calad  a
	stm    #1160,ar3
	ret
