; ROM6 0xB431 ROUTINE_B431 -- 48w, symbols.yaml data_word.
; Evidence: Bound B431-B460 (48w; exit RET FC00@B460, next F074 06B2 = BA32-family head, no overlap); entries 5x F074 call B186/B1F3/B225/B274/B30E (B186 byte-verified F074, rest team objdump)
; ORIGIN 0xB431
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a8
	mvdk   *(0x2639),0x34c9
	cmpm   *(0x34bf),#1
	bc     0xb453,tc
	cmpm   *(0x34bf),#4
	bc     0xb453,tc
	stm    #13456,ar2
	ld     *ar2,b
	and    #-16,b
	stl    b,*ar2
	call   0xb39e
	cmpm   *(0x34bf),#3
	bc     0xb460,ntc
	stm    #10884,ar3
	stm    #1170,ar4
	rpt    #7
	mvdd   *ar3+,*ar4+
	stm    #13456,ar2
	ld     *ar2,b
	and    #-16,b
	or     #1,b
	stl    b,*ar2
	mvdk   *(0x34c9),0x2639
	call   0xb39e
	ret
