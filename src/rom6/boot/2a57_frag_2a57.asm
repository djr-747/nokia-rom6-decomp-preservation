; ROM6 0x2A57 FRAG_2A57 -- 8w, symbols.yaml data_word.
; Evidence: Bound 2A57-2A5E (8w; exit B F073@2A5D->2993 + operand 2A5E, byte-verified (2993 = FRAG_2983 interior, CODE); exit scan clean); entry bc F820@2A3E->2A57 byte-verified (chained from 
; ORIGIN 0x2A57
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#128
	bc     0x2a5f,ntc
	st     #0,*ar3
	b      0x2993
