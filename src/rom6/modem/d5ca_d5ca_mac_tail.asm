; ROM6 0xD5CA D5CA_MAC_TAIL -- 12w, symbols.yaml data_word.
; Evidence: Entered only via 0xD595 banz / 0xD5AC banzd; rptbd mac loop; first exit ret FC00 @D5D5 abutting existing 0xD5D6; zero fall-through; HYPOTHESIS.
; ORIGIN 0xD5CA
	.sect ".text"
	.mmregs
	.global _start
_start:
	sth    a,0x07
	stm    #39,brc
	mvmm   ar4,ar3
	ld     0x07,t
	rptbd  0xd5d4
	ld     #0,asm
	mpy    *ar4+,a
	sfta   a,3
	st     a,*ar3+ || mpy    *ar4+,a
	ret
