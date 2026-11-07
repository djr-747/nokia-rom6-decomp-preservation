; ROM6 0xE50B ROUTINE_E50B -- 27w, symbols.yaml data_word.
; Evidence: Bound E50B-E525 (27w; exit RET FC00@E525 byte-verified, exit scan clean); entries 2x calld F274@ DDA0/DDA6->E50B byte-verified head-exact (call-only entry, pre-word ED00 not post-R
; ORIGIN 0xE50B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,dp
	stm    #4096,ar1
	stm    #256,ar0
	stm    #-1190,ar4
	stm    #-1125,ar5
	stm    #9,brc
	rptbd  0xe524
	stm    #16128,ar6
	sub    *ar2,*ar4-,a
	bcd    0xe51a,agt
	mpya   *ar5-
	mar    *ar6-0
	mar    *ar6+0
	mpy    *ar5+,*ar4+,a
	add    0x11,b
	sfta   b,3
	add    0x16,16,b,a
	st     a,*ar3- || ld     *ar2-,t
	ret
