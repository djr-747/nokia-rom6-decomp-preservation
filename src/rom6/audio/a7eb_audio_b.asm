; ROM6 0xA7EB AUDIO_B -- 27w, symbols.yaml data_word.
; Evidence: Entry F074 0660 61F8 2628 0100 7712; first-RET @0xA805 (len 27); 8 callers AFF6 B0BA B1EA B21C B26B B305 B343 B355; body calls 0x660/0x9E85; FB30 branch excluded; HYPOTHESIS audio 
; ORIGIN 0xA7EB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x660
	bitf   *(0x2628),#256
	stm    #9742,ar2
	ccd    0xabd2,tc
	stm    #555,ar3
	bitf   *(0x2628),#16384
	rc     tc
	bitf   *(0x58f),#15
	bc     0xa803,tc
	bitf   *(0x51d),#512
	rc     tc
	call   0x9e85
	ret
