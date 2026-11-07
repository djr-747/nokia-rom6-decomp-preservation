; ROM6 0x7D74 SUB_7D74 -- 63w, symbols.yaml data_word.
; Evidence: Entry F074 059E 10F8 264F F844 7E02; zero callers (bc @7C6A NOT counted); interior uncond b 7DB1->7DB5 + 7DB9->7E02; shrunk bound 7D74-7DB2 incl operand (linear ret 7E4C abuts exis
; ORIGIN 0x7D74
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	ld     *(0x264f),a
	bc     0x7e02,aneq
	ld     *(0x25a0),a
	ld     #5,b
	cc     0x4590,aeq
	st     #0,*(0x25a0)
	stm    #9785,ar2
	ld     *ar2,b
	and    #12304,b
	sftl   b,2
	andm   #16319,*ar2
	or     *ar2,b
	stl    b,*ar2
	andm   #-17,*ar2
	stm    #9702,ar3
	cmpm   *ar3,#176
	bc     0x7dbb,ntc
	calld  0x807f
	st     #0,*ar3+
	stm    #9717,ar2
	stm    #10951,ar3
	calld  0x7e88
	stm    #14,ar1
	stm    #9785,ar2
	orm    #80,*ar2
	st     #8,*(0x2631)
	bitf   *ar2,#-32768
	bc     0x7db9,ntc
	bitf   *(0x2628),#8
	bc     0x7db3,ntc
	ld     #0,b
	b      0x7db5
