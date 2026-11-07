; ROM6 0x978F SUB_978F -- 78w, symbols.yaml data_word.
; Evidence: True head (978E FC00 is prior 9760-routine exit); entry F7BB; interior CALL 9682; first exit ret FC00 @97DC; bound 978F-97DC; callers @9704/976F verified; HYPOTHESIS.
; ORIGIN 0x978F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st1,intm
	portr  0,*ar2
	andm   #-17,*ar2
	nop
	portw  *ar2,0
	rpt    #18
	nop
	andm   #-2,*(0x20ff)
	bc     0x97a2,aeq
	call   0x9682
	b      0x97dc
	portr  54,*ar2
	andm   #-31,*ar2
	orm    #-32740,*ar2
	nop
	portw  *ar2,54
	nop
	portr  0,*ar2
	orm    #16,*ar2
	nop
	portw  *ar2,0
	rpt    #2
	nop
	call   0x9682
	stm    #96,ar2
	portr  54,*ar2
	bitf   *ar2,#16384
	bc     0x97b9,ntc
	andm   #32767,*ar2
	nop
	portw  *ar2,54
	nop
	portr  0,*ar2
	andm   #-17,*ar2
	nop
	portw  *ar2,0
	rpt    #18
	nop
	ld     *(0x20ff),a
	and    #30,a
	portr  54,*(0xb)
	and    #-31,b
	or     a,b
	nop
	portw  *(0xb),54
	ret
