; ROM6 0x43EA PORT35_DISPATCH -- 73w, symbols.yaml data_word.
; Pool: cala b (5C4F precedent, wave-12). B carries the reada-loaded dispatch word (reada *(0xb) grounded per op_reada, but the CALA target is a runtime value, unbound statically). Otherwise groundable: mvdk/ld-circular (BK flagged), rptb copy, stlm brc/ar6, banz loop, cmpm gate, triple portw pa35.
; Evidence: Entry F074 0594 7714...; first-RET FC00 @0x4432; zero F-refs (branch/table-entered HYPOTHESIS via 4433 cala-b table words 4439/4444/4453/4444/446D/4474); ports pa35 x3 + reada *(0x
; ORIGIN 0x43EA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	stm    #12032,ar4
	ld     *ar4,a
	and    #255,a
	mvdk   *ar2+%,0x13
	ld     *ar2+%,-8,b
	sub    #1,b
	stlm   b,brc
	stlm   b,ar6
	nop
	rptb   0x43fd
	ld     *ar2+%,b
	stl    b,*ar4+
	call   0x2e2f
	stm    #12032,ar4
	add    #17459,a
	reada  *(0xb)
	cala   b
	banz   0x4404,*ar6-
	sub    #17461,a
	rc     aneq
	cmpm   *(0x13),#35
	rc     ntc
	ld     #0,b
	stm    #31,brc
	rptb   0x4419
	nop
	portw  *(0xb),35
	nop
	mar    *ar4-
	stm    #31,brc
	cmpm   *(0x8f1),#162
	bc     0x4425,ntc
	stm    #30,brc
	ld     *ar4,a
	rptb   0x442a
	nop
	portw  *ar4-,35
	nop
	bc     0x4432,ntc
	nop
	portw  *(0x8),35
	nop
	ret
