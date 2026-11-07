; ROM6 0x4986 FRAG_4986 -- 44w, symbols.yaml data_word.
; Evidence: Bound 4986-49B1 (44w, exit F073@49B0->4AD8 + operand); branch-entry F820@494F (objdump bc); zero F074/F274; head 11F8 058C F84F 4996; exit scan clean of RET/FE00/BD/BACC; abuts SUB
; ORIGIN 0x4986
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x58c),b
	bc     0x4996,bleq
	ld     *(0x2656),b
	sub    #15,b
	bc     0x4996,beq
	addm   #-1,*(0x58c)
	andm   #-513,*(0x2a87)
	stm    #96,ar5
	stm    #97,ar4
	ld     *ar2,b
	stm    #9815,ar2
	cmpm   *(0xb),#240
	bc     0x49b6,ntc
	cmpm   *(0x250f),#34
	bc     0x49b2,ntc
	stl    b,*(0x366f)
	stl    b,*(0x37b0)
	cmpm   *(0x34bf),#3
	bc     0x4abe,tc
	b      0x4ad8
