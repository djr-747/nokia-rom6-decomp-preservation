; ROM6 0x96B6 FRAG_96B6 -- 7w, symbols.yaml data_word.
; Evidence: Bound 96B6-96BC (7w; exit RETD FE00@96BA + delays 96BB-96BC (stl 2w), byte-verified; exit scan clean); entries 2x bc F82x@969E/96A2->96B6 byte-verified (both cond tc, exterior from
; ORIGIN 0x96B6
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #6,*(0x20fc)
	ld     #3,a
	retd
	stl    a,*(0x2201)
