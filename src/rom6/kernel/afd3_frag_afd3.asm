; ROM6 0xAFD3 FRAG_AFD3 -- 38w, symbols.yaml data_word.
; Evidence: Bound AFD3-AFF8 (38w, exit FC00@AFF8 objdump-verified); bacc-table arm entry (AFB5-table slot 1 lists AFD3; table bytes verified AFBF/AFD3/AFF9/B017/B04B/B050/B062/B080/B0BD/B0C2 —
; ORIGIN 0xAFD3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x678
	call   0xa2c3
	call   0xa5e1
	cmpm   *(0x2510),#192
	bc     0xaff4,ntc
	bitf   *(0x51f),#6144
	bc     0xaff4,tc
	bitf   *(0x51c),#3
	bc     0xaff4,tc
	ld     *(0x2efe),a
	bc     0xaff4,aneq
	call   0xa8d4
	call   0x9df4
	fcall  0x18019
	fcall  0x18040
	call   0xa7b7
	call   0xa7eb
	ret
