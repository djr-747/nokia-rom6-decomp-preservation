; ROM6 0x51CC HIT_51CC -- 4w, symbols.yaml data_word.
; Evidence: Bound 51CC-51CF (4w; exit RETD FE00@51CD + andm delay 51CE-51CF byte-verified); entries bc F845@51AF->51CC + fall 51CB->51CC (LANE_36F span) + bc F845@51D2->51CC (FRAG_51D0 span) + bc F84D@5183->51CC + bc F830@5188->51CC (ROUTINE_516A span).
; ORIGIN 0x51CC
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	retd
	andm   #-257,*ar4
