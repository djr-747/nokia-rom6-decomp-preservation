; ROM6 0xB39E ROUTINE_B39E -- 19w, symbols.yaml data_word.
; Evidence: Bound B39E-B3B0 (25w; exit RET FC00@B3B0 byte-verified, exit scan clean); entries 2x call F074@ B446/B45E->B39E byte-verified head-exact + post-RET head (FC00@B39D); interior out-c
; ORIGIN 0xB39E
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-19153,ar5
	stm    #-19135,ar6
	ld     #-19137,a
	call   0xaeec
	call   0xa4ba
	stm    #-19153,ar3
	stm    #-19135,ar6
	ld     #-19137,a
	call   0xaf16
	ret
