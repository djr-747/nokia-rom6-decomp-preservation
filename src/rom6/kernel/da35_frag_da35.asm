; ROM6 0xDA35 FRAG_DA35 -- 11w, symbols.yaml data_word.
; Evidence: Bound DA35-DA3F (11w; exit retd FE00@DA3D + delays DA3E-DA3F included per convention; exit scan clean); entry bc F844@DA24->DA35 byte-verified (from FRAG_DA21 [DA21-DA31] interior,
; ORIGIN 0xDA35
	.sect ".text"
	.mmregs
	.global _start
_start:
	addm   #-1,0x58
	ld     0x58,16,a
	add    0x59,16,a
	sub    #30,16,a
	bc     0xda40,ageq
	retd
	st     #32,0x5a
