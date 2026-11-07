; ROM6 0x66E2 FRAG_66E2 -- 43w, symbols.yaml data_word.
; Evidence: Bound 66E2-670C (43w, exit F073@670B->676A + operand); caller bc@66DD; interior calls F074 68A2@66E8 (slice-verified) + 688D@66F8; RECLASSIFIED branch-entered label; HYPOTHESIS fra
; ORIGIN 0x66E2
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x54f),b
	and    #256,b,a
	bc     0x66f2,aeq
	call   0x68a2
	sub    *ar5,b,a
	bc     0x66f2,ageq
	stl    b,*ar5
	st     #1,*(0x56c)
	ld     *(0x54f),b
	and    #-32768,b,a
	bc     0x676a,aeq
	call   0x688d
	sub    *ar5,b,a
	bc     0x676a,ageq
	ld     *ar5,a
	stl    b,*ar5
	add    #4,b
	sub    a,b
	bc     0x6708,beq
	st     #0,*(0x56c)
	orm    #1024,*(0x51e)
	b      0x676a
