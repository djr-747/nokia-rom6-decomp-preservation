; ROM6 0x44AF FRAG_44AF -- 3w, symbols.yaml data_word.
; Evidence: Bound 44AF-44B1 (3w micro: portw pa13 2w + RET FC00@44B1, byte-verified; exit scan clean); entry = post-RET head (RET@44AE = FRAG_44A6 [44A6-44AE] exit, CODE — thin entry per 3AB6 
; ORIGIN 0x44AF
	.sect ".text"
	.mmregs
	.global _start
_start:
	portw  *ar4+,13
	ret
