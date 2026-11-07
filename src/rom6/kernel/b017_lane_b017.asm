; ROM6 0xB017 LANE_B017 -- 31w, symbols.yaml data_word.
; Evidence: Bound B017-B035 (31w, exit F073@B034->B046 + operand B035; objdump b verified); post-RET head; F820/F830 fall-through runs; interior heads B030/B032/B036-note (B036 separate frag p
; ORIGIN 0xB017
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x678
	call   0xa2c3
	call   0xa8bf
	cmpm   *(0x2510),#192
	bc     0xb032,ntc
	fcall  0x1a839
	fcall  0x1a425
	bitf   *(0x51f),#6144
	bc     0xb030,tc
	bitf   *(0x51c),#3
	bc     0xb036,ntc
	call   0xa87f
	call   0xa5e1
	b      0xb046
