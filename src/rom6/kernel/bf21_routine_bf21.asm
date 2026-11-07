; ROM6 0xBF21 ROUTINE_BF21 -- 44w, symbols.yaml data_word.
; Evidence: Bound BF21-BF4C (44w; exit RET FC00@BF4C byte-verified, exit scan clean); entries call F074@BE22-> BF23 interior-projection (in-span, from head+2) + calld F274@BD25->BF21 byte-veri
; ORIGIN 0xBF21
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6de
	call   0xbe22
	ld     #1,asm
	stm    #0,bk
	stm    #2,ar0
	stm    #62,brc
	stm    #-18980,ar7
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 5
	mvdk   *ar7+,0x12
	ld     *ar2+,16,a
	st     a,*ar4+ || ld     *ar2+0%,a
	sth    a,asm,*ar6+
	ld     #0,asm
	rptbd  0xbf45
	stm    #3,ar0
	sub    *ar2,*ar3,a
	adds   0x42,a
	sth    a,asm,*ar5-
	add    *ar2-,*ar3-,b
	adds   0x42,b
	sth    b,asm,*ar6+
	add    *ar2,*ar3,a
	adds   0x42,a
	sth    a,asm,*ar4+
	sub    *ar3-,*ar2+0%,b
	adds   0x42,b
	sth    b,asm,*ar7-
	add    *ar2-,*ar3-,b
	adds   0x42,b
	sth    b,asm,*ar6+
	add    *ar2,*ar3,a
	adds   0x42,a
	sth    a,asm,*ar4+
	ret
