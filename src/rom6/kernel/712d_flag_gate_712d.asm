; ROM6 0x712D FLAG_GATE_712D -- 19w, symbols.yaml data_word.
; Evidence: 6xF074 true CALLs @0x6B22/0x6B86/0x6B93/0x6C1A/0x6ECE/0x6FE1 (call 0x712d @0x6B22 objdump); body F074 05B4 + CMPM *(0x34BF) + RC + BITF *(0x3490); RET FC00 @0x713F; downstream call
; ORIGIN 0x712D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	cmpm   *(0x34bf),#0
	rc     tc
	bitf   *(0x3490),#2
	rc     tc
	cmpm   *(0x34bf),#4
	bc     0x7140,tc
	bitf   *(0x3490),#1
	ret
