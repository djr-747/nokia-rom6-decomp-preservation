; ROM6 0x3A81 ROUTINE_3A81 -- 13w, symbols.yaml data_word.
; Evidence: Bound 3A81-3A8D (13w; exit RET FC00@3A8D byte-verified, exit scan clean); entries calld F274@4D17-> 3A81 byte-verified + post-RET head (FC00@3A80); interior F074@3A81->0632 + F074@
; ORIGIN 0x3A81
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x632
	call   0x3ade
	sub    #64,a,b
	bc     0x3a8e,beq
	sub    #32,a,b
	rc     beq
	ld     #0,a
	ret
