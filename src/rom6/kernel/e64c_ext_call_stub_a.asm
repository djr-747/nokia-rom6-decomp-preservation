; ROM6 0xE64C EXT_CALL_STUB_A -- 40w, symbols.yaml data_word.
; Evidence: Entry F074 05AC 61F8 058F 000F FC20; external call 0x05AC; F830 E671 lane; first-RET @E673 (40w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE64C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ac
	bitf   *(0x58f),#15
	rc     ntc
	bitf   *(0x58f),#2
	bc     0xe671,tc
	calld  0x2282
	stm    #12,ar2
	rc     ntc
	bitf   *(0x58f),#-4096
	bc     0xe671,tc
	stm    #10217,ar3
	stm    #158,ar4
	stm    #2,ar5
	st     #4,*ar3
	call   0x2c88
	andm   #4095,*(0x58f)
	orm    #4096,*(0x58f)
	fcall  0x1aa02
	ret
