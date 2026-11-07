; ROM6 0x8334 LEAF54_82FF -- 56w, symbols.yaml data_word.
; Evidence: Entry F6BE EA00 7715 0006 E900 6F86; RET @8334 len 56 (wave-11 correction: len-54 arithmetic cut the orm@8369 operands 836A-836B mid-instruction; +2w to complete, recombination-cle
; ORIGIN 0x8334
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
	call   0x66e
	stm    #10884,ar2
	stm    #10891,ar1
	ld     *(0x2631),a
	add    *(0x2630),a
	add    #-31931,a
	and    #-1,a
	reada  *(0xb)
	bacc   b
	sth    b,0x4e
	sth    b,0x6d
	sth    b,*ar4-
	sth    b,*ar0-0B
	sth    b,*ar4+0
	sth    b,*ar6-0%
	sth    b,*+ar0(0x83ff)
	ldm    ar7,b
	bc     0x835d,bneq
	calld  0x82d4
	stm    #-8909,ar6
	stm    #-20108,ar6
	calld  0x7f95
	stm    #-13,t
	b      0x8365
	call   0x7fc0
	stm    #-20108,ar6
	calld  0x7f95
	stm    #-5,t
	calld  0x7fc6
	stm    #10884,ar2
	orm    #512,*(0x2a87)
