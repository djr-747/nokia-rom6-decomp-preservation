; ROM6 0xC660 FRAG_C660 -- 31w, symbols.yaml data_word.
; Evidence: Bound C660-C67E (31w; first-RET FC00@C67E byte-verified; interior F274@C671->0696 out-call kept); post-RET head; zero callers; RET-heads @C6B1/@C716 no entry evidence, stay dark; H
; ORIGIN 0xC660
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar0
	stm    #18,ar0
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 10
	pshd   *ar0+
	ssbx   st1,frct
	ld     #0,asm
	stm    #4709,ar2
	stl    a,*ar2
	stm    #8722,ar3
	stm    #4708,ar4
	stm    #4712,ar5
	calld  0x696
	stm    #0,brc
	rsbx   st1,frct
	stm    #28,ar0
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 10
	popd   *ar0-
	popm   ar0
	ld     *(0x1265),a
	ret
