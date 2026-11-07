; ROM6 0x9CCF FRAG_9CCF -- 24w, symbols.yaml data_word.
; Evidence: Bound 9CCF-9CE6 (24w; NO exit-class in-span — falls into 9CE7 zone; east claim F073@9CDB->9C12 FALSIFIED (w[9CDB]=1092, not F073); pre-word 9CE7 = next-zone value, not post-RET); e
; ORIGIN 0x9CCF
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x860),#2
	bc     0x9ce7,ntc
	stm    #10697,ar2
	mvmm   ar2,ar4
	stm    #79,brc
	rptb   0x9ce5
	ld     *ar2+,a
	call   0x6b8
	stl    a,8,*ar4
	ld     *ar2+,a
	call   0x6b8
	and    #255,a
	or     *ar4,a
	stl    a,*ar4+
	ld     #79,b
