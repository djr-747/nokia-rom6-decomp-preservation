; ROM6 0x6954 FRAG_6954 -- 13w, symbols.yaml data_word.
; Evidence: Bound 6954-6960 (exit F073@695F->692C + operand 6960); B-join entries 693E/694B (no calls); HYPOTHESIS.
; ORIGIN 0x6954
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #8,a
	add    *(0x564),a
	stl    a,*(0x564)
	sub    #16,a
	rc     ageq
	addm   #1,*(0x60)
	b      0x692c
