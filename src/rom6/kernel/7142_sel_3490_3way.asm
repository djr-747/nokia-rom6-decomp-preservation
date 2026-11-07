; ROM6 0x7142 SEL_3490_3WAY -- 37w, symbols.yaml data_word.
; Evidence: Entry F074 05B4; bound 7142-7166 (exits 7154/715D/7166 all FC00 verified); callers 6C2E/6C3A/6D2C/6D38/6EF7; bitf *(3490)#1/#2 cascade + stm ar2 lanes; HYPOTHESIS.
; ORIGIN 0x7142
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	bitf   *(0x3490),#1
	bc     0x7155,tc
	bitf   *(0x3490),#2
	bc     0x715e,tc
	xc     2,aeq
	stm    #13526,ar2
	st     #0,*(0x533)
	ret
	st     #0,*(0x37f6)
	stm    #13538,ar2
	xc     2,aneq
	stm    #13438,ar2
	ret
	st     #0,*(0x37f7)
	stm    #13550,ar2
	xc     2,aneq
	stm    #13446,ar2
	ret
