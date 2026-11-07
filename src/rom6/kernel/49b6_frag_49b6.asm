; ROM6 0x49B6 FRAG_49B6 -- 65w, symbols.yaml data_word.
; Evidence: Bound 49B6-49F6 (65w; exit F073@49F5->49FA + operand 49F6, byte-verified); entry bc F820@49A0-> 49B6 byte-verified (cond, sole exterior entry); interior join F073@49D6->49DE in-spa
; ORIGIN 0x49B6
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x250f),#34
	bc     0x49d8,ntc
	cmpm   *(0x34bf),#1
	bc     0x49d0,tc
	cmpm   *(0x34bf),#4
	bc     0x49d0,tc
	ld     *(0x366f),a
	bcd    0x4ae0,aeq
	st     #1,*ar5
	cmpm   *(0x34bf),#3
	bc     0x49de,ntc
	ld     *(0x37b0),a
	bcd    0x4ae0,aeq
	st     #1,*ar5
	b      0x49de
	ld     *(0x2656),a
	bcd    0x4ae0,aeq
	st     #1,*ar5
	cmpm   *(0x250f),#34
	bc     0x4a19,ntc
	cmpm   *(0x34bf),#3
	bc     0x4a01,ntc
	cmpm   *(0x366f),#15
	bc     0x49f7,ntc
	st     #0,*(0x366f)
	cmpm   *(0x37b0),#15
	bc     0x4a1e,tc
	b      0x4a4b
