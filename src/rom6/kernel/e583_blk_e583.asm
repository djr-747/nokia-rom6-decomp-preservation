; ROM6 0xE583 BLK_E583 -- 26w, symbols.yaml data_word.
; Evidence: Post-RET head; EXIT CORRECTED by all-paths walk: sole exit retd FE00 @E59A +2 delay words (E59B add a,b; E59C sfta); true end E59C span 26 (not 163); xc-only interior; no callers l
; ORIGIN 0xE583
	.sect ".text"
	.mmregs
	.global _start
_start:
	sth    a,0x7d
	sub    0x7d,16,a
	sfta   a,6
	sth    a,0x12
	ldm    al,a
	sfta   a,-1
	stl    a,0x7e
	mar    *+ar2(0xfaa8)
	ld     *ar2+,16,b
	sub    *ar2-,16,b,a
	masa   0x7e,b
	ld     #29,a
	sub    0x7d,a
	neg    a
	stlm   a,t
	add    #16,a
	norm   b
	nop
	xc     1,alt
	sfta   b,-16
	ld     #1,a
	retd
	add    a,b
	sfta   b,-1,a
