; ROM6 0xAE49 FRAG_AE49 -- 35w, symbols.yaml data_word.
; Evidence: Bound AE49-AE6B (35w; exit RET FC00@AE6B byte-verified); post-RET head (pre FC00@AE48); zero callers; interior call AE22@AE4C (objdump call), join F073@AE63->AE6A; abuts JUMP_TABLE
; ORIGIN 0xAE49
	.sect ".text"
	.mmregs
	.global _start
_start:
	addm   #1,*ar2
	ldm    ar5,a
	call   0xae22
	bitf   *(0x3ec8),#2
	bc     0xae65,ntc
	stm    #9718,ar2
	stm    #9720,ar5
	mvdd   *ar5+,*ar2+
	mvdd   *ar5+,*ar2+
	mvmd   ar2,0x265e
	stm    #9730,ar2
	stm    #9732,ar5
	mvdd   *ar5+,*ar2+
	mvdd   *ar5+,*ar2+
	mvmd   ar2,0x2660
	b      0xae6a
	bitf   *(0x3ec8),#32
	cc     0xae1b,ntc
	stlm   a,ar5
	ret
