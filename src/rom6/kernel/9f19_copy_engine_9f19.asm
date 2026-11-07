; ROM6 0x9F19 COPY_ENGINE_9F19 -- 15w, symbols.yaml data_word.
; Evidence: PSHM AL/AH/AG/ST1, LD *AR2, RPTB->0x9F22, MVDD *AR3,*AR2+, ST A,*AR3+, POPM x4; RET 0x9F27; called by stagers 0x9F28/0x9F35 (F274 9F19). Bound 9F19-9F27 (wave-5: exit FC00@9F27 + p
; ORIGIN 0x9F19
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   al
	pshm   ah
	pshm   ag
	pshm   st1
	ld     *ar2,16,a
	ld     #0,asm
	rptb   0x9f22
	mvdd   *ar3,*ar2+
	st     a,*ar3+ || ld     *ar2,a
	popm   st1
	popm   ag
	popm   ah
	popm   al
	ret
