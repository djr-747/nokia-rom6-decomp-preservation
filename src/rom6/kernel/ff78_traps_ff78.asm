; ROM6 0xFF78 TRAPS_FF78 -- 72w, symbols.yaml data_word.
; Evidence: Bound FF78-FFBF (72w: 8w data head 0000 0000 5800 F741 5412 B3E6 4F26 00E3 + trap stubs F073 FF85@FF82 / F073 0F00@FF85 boot target + retf + F49B/F495 fill FF90-FFBF fully read); z
; ORIGIN 0xFF78
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @FF78 0000 add    0x00,a
	add    0x00,a
	; @FF79 0000 add    0x00,a
	add    0x00,a
	; @FF7A 5800 drsub  0x00,a
	drsub  0x00,a
	; @FF7B f741 ld     b,1,b
	ld     b,1,b
	; @FF7C 5412 dsub   0x12,a
	dsub   0x12,a
	; @FF7D b0e6 mac    *ar4+0%,*ar4-,a
	mac    *ar4+0%,*ar4-,a
	; @FF7E 4f26 dst    b,0x26
	dst    b,0x26
	; @FF7F 00e3 add    *ar3(0x771d),a
	add    *ar3(0x771d),a
	.word 0xFFA8 ; XC: gas encoder gap
	; @FF82 f073 b      0xff85
	b      0xff85
	; @FF84 f49b retf
	retf
	; @FF85 f073 b      0xf00
	b      0xf00
	; @FF87 0006 add    0x06,a
	add    0x06,a
	; @FF88 f49b retf
	retf
	; @FF89 f495 nop
	nop
	; @FF8A f495 nop
	nop
	; @FF8B f495 nop
	nop
	; @FF8C f49b retf
	retf
	; @FF8D f495 nop
	nop
	; @FF8E f495 nop
	nop
	; @FF8F f495 nop
	nop
	; @FF90 f49b retf
	retf
	; @FF91 f495 nop
	nop
	; @FF92 f495 nop
	nop
	; @FF93 f495 nop
	nop
	; @FF94 f49b retf
	retf
	; @FF95 f495 nop
	nop
	; @FF96 f495 nop
	nop
	; @FF97 f495 nop
	nop
	; @FF98 f49b retf
	retf
	; @FF99 f495 nop
	nop
	; @FF9A f495 nop
	nop
	; @FF9B f495 nop
	nop
	; @FF9C f49b retf
	retf
	; @FF9D f495 nop
	nop
	; @FF9E f495 nop
	nop
	; @FF9F f495 nop
	nop
	; @FFA0 f49b retf
	retf
	; @FFA1 f495 nop
	nop
	; @FFA2 f495 nop
	nop
	; @FFA3 f495 nop
	nop
	; @FFA4 f49b retf
	retf
	; @FFA5 f495 nop
	nop
	; @FFA6 f495 nop
	nop
	; @FFA7 f495 nop
	nop
	; @FFA8 f49b retf
	retf
	; @FFA9 f495 nop
	nop
	; @FFAA f495 nop
	nop
	; @FFAB f495 nop
	nop
	; @FFAC f49b retf
	retf
	; @FFAD f495 nop
	nop
	; @FFAE f495 nop
	nop
	; @FFAF f495 nop
	nop
	; @FFB0 f49b retf
	retf
	; @FFB1 f495 nop
	nop
	; @FFB2 f495 nop
	nop
	; @FFB3 f495 nop
	nop
	; @FFB4 f49b retf
	retf
	; @FFB5 f495 nop
	nop
	; @FFB6 f495 nop
	nop
	; @FFB7 f495 nop
	nop
	; @FFB8 f49b retf
	retf
	; @FFB9 f495 nop
	nop
	; @FFBA f495 nop
	nop
	; @FFBB f495 nop
	nop
	; @FFBC f49b retf
	retf
	; @FFBD f495 nop
	nop
	; @FFBE f495 nop
	nop
	; @FFBF f495 nop
	nop
