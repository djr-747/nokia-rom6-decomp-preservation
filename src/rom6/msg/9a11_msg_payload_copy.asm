; ROM6 0x9A11 MSG_PAYLOAD_COPY -- 38w, symbols.yaml data_word.
; Evidence: Called from 0x9429; CALL 0x5D0 guard; LD #250 - *(0x2200) space check; RPT *(0x08) block move *ar2+ -> *ar3+0%; ORM #0x1000 *(0x20FF) done flag. Bound 9A11-9A36 (wave-5: exit retd 
; ORIGIN 0x9A11
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5d0
	rc     bleq
	ld     #250,1,a
	sub    *(0x2200),a
	sub    b,a
	rc     aleq
	sfta   b,-1,a
	bitf   *(0x20ff),#4096
	bc     0x9a37,tc
	bcd    0x9a2f,nc
	stm    #1,ar0
	rpt    *(0x8)
	mvdd   *ar2+,*ar3+0%
	mar    *ar3-%
	ssbx   st1,intm
	orm    #4096,*(0x20ff)
	reted
	mvmd   ar3,0x21fc
	add    #-1,a
	rpt    *(0x8)
	mvdd   *ar2+,*ar3+0%
	retd
	mvmd   ar3,0x21fc
