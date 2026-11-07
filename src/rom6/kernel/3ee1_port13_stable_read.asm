; ROM6 0x3EE1 PORT13_STABLE_READ -- 1w, symbols.yaml program_word.
; Evidence: RF-program sweep, RET at 0x3FC3. Stable pa13 read, INTM-locked pa2 RMW, sequenced pa14/15/4/9/5/7/10/47/13/11/8/0/1/32/33/42/48/3/43 writes, two CALL 0x4007.
; ORIGIN 0x3EE1
	.sect ".text"
	.global _start
_start:
	call   0x63e
