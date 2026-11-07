; ROM6 0x68B7 ROUTINE_68B7 -- 19w, symbols.yaml data_word.
; Evidence: Bound 68B7-68C9 (19w; exit RET FC00@68C9 byte-verified; interior conds F844@68B9/F846@68C0/F843@ 68C6 all ->68C9 (leaf-fan into exit); exit scan otherwise clean); entries calld F27
; ORIGIN 0x68B7
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	ld     *ar0,a
	bc     0x68c9,aneq
	ld     *ar1,a
	sub    *ar6,a
	stm    #2325,ar2
	sub    *ar2,a
	bc     0x68c9,agt
	ld     *ar1,a
	add    #3,a
	sub    *ar2,a
	bc     0x68c9,alt
	ld     #1,b
	ret
