; ROM6 0xBA32 DELAY_UPDATE_BA32 -- 36w, symbols.yaml data_word.
; Evidence: Entry E801 00F8 2AF1; pure RPTBD-MVDD delay shuffle, no subcalls; first-RET @0xBA55 (len 36); 2 F074 callers B740 B805 (B740 objdump-verified call 0xBA32).
; ORIGIN 0xBA32
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #1,a
	add    *(0x2af1),a
	ld     #119,b
	min    b
	stlm   b,brc
	stm    #12056,ar2
	stm    #12206,ar3
	stm    #10137,ar4
	rptbd  0xba43
	stm    #10257,ar5
	mvdd   *ar2+,*ar4+
	mvdd   *ar3+,*ar5+
	ld     #2,a
	add    *(0x2af1),a
	sub    #120,a
	rc     aleq
	add    #-1,a
	stlm   a,brc
	stm    #3976,ar4
	rptbd  0xba54
	stm    #4036,ar5
	mvdd   *ar2+,*ar4+
	mvdd   *ar3+,*ar5+
	ret
