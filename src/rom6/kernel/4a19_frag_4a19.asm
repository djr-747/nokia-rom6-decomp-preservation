; ROM6 0x4A19 FRAG_4A19 -- 45w, symbols.yaml data_word.
; Evidence: Bound 4A19-4A45 (45w; exit F073@4A44->4A12 + operand 4A45, byte-verified, back-edge to FRAG_4A12 head — lane-loop close); entry bc F820@49E1->4A19 byte-verified (cond); interior jo
; ORIGIN 0x4A19
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#15
	bc     0x4a4b,ntc
	st     #15000,*ar4
	nop
	portw  *ar4,5
	rpt    #22
	nop
	nop
	portw  *ar4,6
	rpt    #22
	nop
	nop
	portw  *ar4,47
	rpt    #22
	nop
	nop
	portw  *ar4,7
	rpt    #22
	nop
	nop
	portw  *ar4,8
	rpt    #16
	nop
	cmpm   *(0x250f),#34
	bc     0x4a46,ntc
	st     #0,*(0x366f)
	st     #0,*(0x37b0)
	b      0x4adf
