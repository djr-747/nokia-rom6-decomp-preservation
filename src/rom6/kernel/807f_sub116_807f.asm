; ROM6 0x807F SUB116_807F -- 36w, symbols.yaml data_word.
; Evidence: Entry F074 059E F274 3A27 E732 E801; BOUND CORRECTED entry-linear: straight-line to first exit retd @0x80A0, bound 807F-80A2 (incl delay); was 80F2 (overclaim); 7 callers incl ext 
; ORIGIN 0x807F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	calld  0x3a27
	mvmm   ar3,ar2
	ld     #1,a
	calld  0x3ab6
	stm    #12182,ar2
	stm    #12182,ar2
	xorm   #65535,*ar2+
	xorm   #65535,*ar2+
	xorm   #65535,*ar2+
	mar    *ar2-
	ld     *ar2-,16,a
	and    #-256,16,a
	ldu    *ar2-,b
	or     b,8,a
	ldu    *ar2,b
	or     b,-8,a
	mar    *+ar3(0xd)
	sth    a,*ar3-
	stl    a,*ar3-
	andm   #255,*ar3
	sfta   b,8
	retd
	or     *ar3,b
	stl    b,*ar3
