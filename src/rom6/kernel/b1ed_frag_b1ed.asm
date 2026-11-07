; ROM6 0xB1ED FRAG_B1ED -- 50w, symbols.yaml data_word.
; Evidence: Bound B1ED-B21E (35w, exit FC00@B21E); bacc-table arm (table B177-B17C); interior join F073@B20E->B21A; HYPOTHESIS.
; ORIGIN 0xB1ED
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xb358
	call   0xa3e1
	call   0xa2c3
	call   0xb431
	call   0xa4d5
	call   0xb3e2
	andm   #-16,*(0x3490)
	call   0xb3b1
	ld     *(0x34bf),a
	bc     0xb21a,aeq
	sub    #4,a
	bc     0xb210,aeq
	stm    #13456,ar2
	andm   #-16,*ar2
	orm    #1,*ar2
	call   0xb3b1
	b      0xb21a
	stm    #13509,ar2
	mvdk   *ar2,0x37dd
	st     #0,*ar2+
	mvdk   *ar2,0x34c7
	st     #0,*ar2
	call   0xa7b7
	call   0xa7eb
	ret
