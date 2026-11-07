; ROM6 0xE532 SUB25_E532 -- 25w, symbols.yaml data_word.
; Evidence: Post-retd head (retd @E52F + delays E530/E531); entry ED00 7715 0000; first exit ret @E54A len 25 entry-linear, no inner calls; callers F274 @D17D/E0F5 verified; HYPOTHESIS.
; Wave-12: exit ret @E54A owned here; ret-first twin e54a_sub25_e532.asm deleted (was ret@E54A + dup of e54b head E54B-E562); e54b owns its head (EXPECT starts F847, no ret-dup).
; ORIGIN 0xE532
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,asm
	stm    #0,ar5
	mpy    *ar2,*ar3+,a
	sfta   a,3
	sth    a,*ar4+
	mpy    *ar2+,*ar3-,a
	mac    *ar2+,*ar3,a
	rptbd  0xe549
	sfta   a,3
	sth    a,*ar4+
	mpy    *ar2-,*ar3+,a
	rpt    0x15
	mac    *ar2-,*ar3+,a
	mac    *ar2,*ar3+,a
	sfta   a,3
	st     a,*ar4+ || ld     *ar5+,a
	mpy    *ar2+,*ar3-,a
	rpt    0x15
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3,a
	sfta   a,3
	st     a,*ar4+ || ld     *ar5+,a
	ret
