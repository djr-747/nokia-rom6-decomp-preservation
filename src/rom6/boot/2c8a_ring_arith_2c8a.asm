; ROM6 0x2C8A RING_ARITH_2C8A -- 43w, symbols.yaml program_word.
; Evidence: Fall-through from 2c88 ring-report gate (prev span); B-compare/add lane, ldm/sftl scale, dual rc guards, st block build, ld/stm preset, dark 93CE call, B-clear ret; interior bc/b joins; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x2C8A
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x8e5),b
	sub    *(0x8e4),b,a
	bc     0x2c93,agt
	add    #100,a
	ldm    ar5,b
	add    #3,b
	sftl   b,-1
	sub    b,a
	bc     0x2cb5,agt
	ld     #0,b
	bitf   *(0x3ec8),#2
	rc     ntc
	bitf   *(0x54d),#12
	rc     ntc
	stm    #12032,ar2
	st     #1025,*ar2+
	st     #372,*ar2+
	st     #4608,*ar2
	ld     #5,b
	stm    #12032,ar2
	ld     #20,a
	stm    #244,ar0
	call   0x93ce
	ld     #0,b
	ret
