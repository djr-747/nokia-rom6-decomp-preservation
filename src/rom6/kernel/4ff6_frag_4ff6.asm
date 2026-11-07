; ROM6 0x4FF6 FRAG_4FF6 -- 21w, symbols.yaml data_word.
; Evidence: Bound 4FF6-500A (exit bd@5007->0x1000 OUT, uncond branch-out; delay words 5009/500A now included — wave-11 spill fix, old note left them unowned); post-retd abut, zero callers; cmp
; ORIGIN 0x4FF6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	cmpm   *(0x250f),#34
	bc     0x5002,ntc
	bitf   *(0x3aca),#16
	bc     0x500b,tc
	bitf   *(0x51c),#3
	bc     0x5052,tc
	bd     0x1000
	ld     *(0x2f1f),a
