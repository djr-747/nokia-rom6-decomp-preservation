; ROM6 0xB080 LANE_B080 -- 33w, symbols.yaml data_word.
; Evidence: Bound B080-B0A0 (33w, exit F073@B09F->B0A9 + operand); post-RET head; F84C bc@B086 + F820/F830 fall- throughs; interior B09D/B0A1-note (B0A1 separate frag); out-calls 067A/A2C3/A4D
; ORIGIN 0xB080
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67a
	call   0xa2c3
	call   0xa4de
	bc     0xb0a9,bneq
	call   0xa8bf
	cmpm   *(0x2510),#192
	bc     0xb0a9,ntc
	fcall  0x1a839
	fcall  0x1a425
	bitf   *(0x51f),#6144
	bc     0xb09d,tc
	bitf   *(0x51c),#3
	bc     0xb0a1,ntc
	call   0xa87f
	b      0xb0a9
