; ROM6 0xA109 AUDIO_SELECT_A109 -- 34w, symbols.yaml data_word.
; Evidence: Entry F074 061C + 61F8 0577 0420 + F820 A12A + 11F8 2AEE loads; RET FC00 @0xA12A; callers F074 @0xA6DF/0xA8F7/0xAA13 (0xA6DF verified). Bound A109-A12A (wave-5: exit + post-RET byt
; ORIGIN 0xA109
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x61c
	bitf   *(0x577),#1056
	bc     0xa12a,ntc
	ld     *(0x2aee),b
	ld     #15,a
	and    a,b
	bc     0xa126,bneq
	bitf   *(0x2b08),#1
	bc     0xa120,tc
	ld     *(0x2aeb),b
	and    a,b
	bc     0xa126,bneq
	dld    *(0x238),a
	dst    a,*(0x23a)
	b      0xa12a
	dld    *(0x23a),a
	dst    a,*(0x238)
	ret
