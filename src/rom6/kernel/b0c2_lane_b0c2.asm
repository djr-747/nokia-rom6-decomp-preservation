; ROM6 0xB0C2 LANE_B0C2 -- 38w, symbols.yaml data_word.
; Evidence: Bound B0C2-B0E7 (38w, exit F073@B0E6->B0F0 + operand); post-RET head; F845@B0CD + F820/F830 fall- throughs; interior B0E4/B0E8-note (B0E8 open, no entry); out-calls 067A/A2C3/A361/
; ORIGIN 0xB0C2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67a
	call   0xa2c3
	call   0xa361
	rc     aneq
	call   0xa4de
	call   0xa482
	bc     0xb0f0,aeq
	call   0xa8bf
	cmpm   *(0x2510),#192
	bc     0xb0f0,ntc
	fcall  0x1a839
	fcall  0x1a425
	bitf   *(0x51f),#6144
	bc     0xb0e4,tc
	bitf   *(0x51c),#3
	bc     0xb0e8,ntc
	call   0xa87f
	b      0xb0f0
