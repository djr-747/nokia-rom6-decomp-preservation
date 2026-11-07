; ROM6 0x454F SUB_454F -- 8w, symbols.yaml data_word.
; Evidence: Bound 454F-4556 (8w, FC00@4556); caller F074@4546 (objdump call; site inside killed-draft zone, used as evidence only); post-ret head; interior F5E2 cala (computed call, returns); 
; ORIGIN 0x454F
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #17751,a
	reada  *(0xb)
	cala   b
	banz   0x4551,*ar6-
	ret
