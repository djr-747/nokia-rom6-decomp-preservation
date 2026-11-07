; ROM6 0x4EE0 SUB_4EE0 -- 19w, symbols.yaml data_word.
; Evidence: Bound 4EE0-4EF2 (exit F273 bd@4EEF->4EF9 + delays); callers F274 @4BC5/4D68; HYPOTHESIS.
; ORIGIN 0x4EE0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	ld     *(0x2f1f),8,a
	mvdm   0x2f1e,ar3
	stm    #12123,ar2
	banz   0x4ef3,*ar3
	stm    #2322,ar3
	stm    #9482,ar4
	bd     0x4ef9
	ld     *(0x250e),b
