; ROM6 0xB15C LEAF_B15C -- 16w, symbols.yaml data_word.
; Evidence: Bound B15C-B16B (16w, exit FC00@B16B); bacc-table arm (table B129-B12E); interior rc FC44@B160 (passed) + cc F944 A91C (conditional call, interior); out-calls A2C3/A361/A4DE/A482 +
; ORIGIN 0xB15C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	call   0xa361
	rc     aneq
	call   0xa4de
	call   0xa482
	cc     0xa91c,aneq
	calld  0xa2b9
	stm    #-8625,ar5
	ret
