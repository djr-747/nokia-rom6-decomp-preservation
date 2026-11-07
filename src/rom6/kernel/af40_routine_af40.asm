; ROM6 0xAF40 ROUTINE_AF40 -- 23w, symbols.yaml data_word.
; Evidence: Bound AF40-AF56 (23w; exit RET FC00@AF56 byte-verified, exit scan clean); entries 2x call F074@ B3BB/B424->AF40 byte-verified head-exact (call-only entry, pre-word 059A not post-RE
; ORIGIN 0xAF40
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar1
	ld     #0,a
	cmpm   *(0x250f),#34
	bc     0xaf4b,ntc
	ld     *(0x3490),a
	and    #7,a
	stl    a,*(0x11)
	nop
	nop
	mvdk   *ar1(0xb55f),0x352c
	mvdk   *ar1(0xb562),0x352d
	popm   ar1
	ret
