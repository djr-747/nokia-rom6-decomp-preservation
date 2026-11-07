; ROM6 0xE9C8 ZEROFILL_STUB_2RANGE -- 14w, symbols.yaml data_word.
; Evidence: CODE not data: entry E800 80F8 294B 7710 297A EC17 8090 7710 241A EC2F 8090 8A09 8A08 F4E6 (ld #0,a / stl / stm / rpt-clear x2 / popm / fbacc a); clears 24w @0x297A + 48w @0x241A; 
; Pool: FBACC computed far jump (oracle-unbound dispatch; zerofill head modelable but homeless); stays .asm, bytes verified.
; ORIGIN 0xE9C8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	stl    a,*(0x294b)
	stm    #10618,ar0
	rpt    #23
	stl    a,*ar0+
	stm    #9242,ar0
	rpt    #47
	stl    a,*ar0+
	popm   ah
	popm   al
	fbacc  a
