; ROM6 0x93CE MSG_CLASSIFY_BY_CALLER -- 70w, symbols.yaml data_word.
; Evidence: Entry CALL 0x5BC; MVMM SP,AR3 + LD *ar3+ reads caller stacked regs; CMPM lanes vs dispatcher return- PCs 0x2D5D/0x2DDB and AND #255 low-byte lanes vs 0x4D/0x9A/0x05/0x50/0x9C; 8 CA
; ORIGIN 0x93CE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5bc
	bitf   *(0x3ec8),#2
	bc     0x9414,ntc
	bitf   *(0x54d),#96
	mvmm   sp,ar3
	bc     0x9414,ntc
	cmpm   *ar3,#11613
	bc     0x93e3,tc
	cmpm   *ar3,#11739
	bc     0x9414,ntc
	mvmm   ar2,ar3
	pshm   al
	pshm   ah
	pshm   ag
	mar    *ar3+
	ld     *ar3,a
	and    #255,a
	stm    #8,ar3
	bitf   *(0x54d),#64
	bc     0x93fe,ntc
	cmpm   *ar3,#77
	bc     0x9410,tc
	cmpm   *ar3,#154
	bc     0x9410,tc
	cmpm   *ar3,#5
	bc     0x9410,tc
	bitf   *(0x54d),#32
	bc     0x940b,ntc
	cmpm   *ar3,#80
	bc     0x9410,tc
	cmpm   *ar3,#156
	bc     0x9410,tc
	popm   ag
	popm   ah
	popm   al
	b      0x9414
	popm   ag
	popm   ah
	popm   al
	ret
