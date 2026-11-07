; ROM6 0x39A4 ROUTINE_PA60_57 -- 76w, symbols.yaml data_word.
; Evidence: Entry F074/0630 (objdump call 0x630; callers 2BE9-F074 + B399-F274); portw pa60 x4 (0x39A8/0x39AD/0x39CB/0x39D0) + pa57 x2 (0x39C0/0x39C5); first-RET FC00 @0x39EF; adjacent leaf 0x
; ORIGIN 0x39A4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x630
	ld     #3,a
	nop
	portw  *(0x8),60
	ld     #5,a
	nop
	portw  *(0x8),60
	stm    #3,brc
	rptb   0x39b7
	nop
	portw  *ar3+,57
	nop
	ld     *ar2+,16,a
	sfta   a,-5
	add    *ar2,16,a
	sfta   a,-6
	add    *ar2(0x5),16,a
	sfta   a,-5
	nop
	portw  *(0x8),57
	nop
	nop
	portw  *(0x9),57
	ld     #-4,a
	nop
	portw  *(0x8),60
	ld     #2,a
	nop
	portw  *(0x8),60
	bitf   *(0x7),#2048
	ssbx   st1,intm
	portr  0,*(0x8)
	or     #96,a
	nop
	portw  *(0x8),0
	rpt    #21
	nop
	xc     1,ntc
	rsbx   st1,intm
	portr  56,*(0x8)
	and    #16,a
	or     #9,a
	nop
	portw  *(0x8),56
	ret
