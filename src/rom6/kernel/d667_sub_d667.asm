; ROM6 0xD667 SUB_D667 -- 55w, symbols.yaml data_word.
; Evidence: Entry EA14 6160 0002 after ret D666; caller F074 @D7CB (objdump call); calls DB4A DC18 E4CB; first- RET ret @D69D via b D692; HYPOTHESIS. Bound D667-D69D (wave-5: exit FC00@D69D + 
; ORIGIN 0xD667
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #20,dp
	bitf   0x60,#2
	bc     0xd674,ntc
	stm    #2766,ar2
	stm    #2864,ar4
	calld  0xdb4a
	stm    #2776,ar3
	ld     0x60,a
	and    #112,a,b
	bc     0xd69e,beq
	and    #64,a
	bc     0xd683,aeq
	calld  0xdc18
	stm    #12611,ar5
	b      0xd692
	stm    #2874,ar3
	stm    #2884,ar4
	ld     #9,a
	stlm   a,brc
	stm    #12611,ar5
	rptbd  0xd691
	stm    #3104,ar6
	mvdd   *ar4,*ar3+
	mvdd   *ar4+,*ar5+
	sth    a,*ar6+
	stm    #3124,ar4
	rpt    #9
	mvkd   0x3143,*ar4+
	mvdm   0x300c,ar3
	calld  0xe4cb
	stm    #12611,ar2
	ret
