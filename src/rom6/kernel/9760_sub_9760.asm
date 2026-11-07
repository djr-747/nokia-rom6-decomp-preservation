; ROM6 0x9760 SUB_9760 -- 47w, symbols.yaml data_word.
; Evidence: Bound 9760-978E (47w; exit RET FC00@978E, matches existing SUB_978F note: prior-routine exit); entry F074 05C2; caller F074@0x9958 byte-verified; interior rc FC4D@976C passes, call
; ORIGIN 0x9760
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5c2
	ld     *(0x2200),a
	rcd    aneq
	stm    #96,ar2
	portr  54,*(0x8)
	and    #4096,a,b
	rc     beq
	and    #2048,a
	call   0x978f
	stm    #96,ar2
	st     #1024,*ar2
	nop
	portw  *ar2,1
	rpt    #22
	nop
	portr  2,*ar2
	orm    #768,*ar2
	andm   #-1025,*ar2
	nop
	portw  *ar2,2
	rsbx   st1,intm
	bitf   *(0x20ff),#2
	rcd    ntc
	stm    #149,ar2
	calld  0x2d5e
	stm    #2157,ar3
	ret
