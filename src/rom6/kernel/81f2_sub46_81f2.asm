; ROM6 0x81F2 SUB46_81F2 -- 46w (overlap-split wave-12).
; Evidence: Bound 81F2-821F; entry F074 066E (call 0x66E dark); 4 callers calld/call @817F/@819A/@81A3/@81B5 (810A-region, objdump-verified 2026-11-07); interior calld 0x8220 @81F9 (frag_8220 extern); exit ret FC00 @821F. Carved from 81f1_sub232_810a.asm head (deleted: it swallowed 8220/82a5/82cb); mis-origin draft 821f_sub46_81f2.asm deleted (its evidence described THIS span, its bytes duplicated ret@821F + 8220 head). Recombine-clean.
; ORIGIN 0x81F2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x66e
	st     #0,*(0x2578)
	stm    #9599,ar2
	calld  0x8220
	stm    #10918,ar3
	stm    #9600,ar3
	stm    #10918,ar2
	ld     *ar2,a
	and    #-249,a
	ld     *ar3+,3,b
	and    #248,b
	or     b,a
	stl    a,*ar2+
	ld     *ar3-,16,a
	or     *ar3+,a
	ld     a,-5,a
	ld     *ar2,8,b
	and    #255,a
	or     b,a
	stl    a,*ar2+
	ld     *ar3-,16,a
	or     *ar3+,a
	ld     a,-13,a
	ld     *ar2,b
	and    #15,a
	or     b,8,a
	stl    a,*ar2+
	stm    #27,brc
	rptb   0x821e
	ld     *ar2,8,a
	stl    a,*ar2+
	ret
