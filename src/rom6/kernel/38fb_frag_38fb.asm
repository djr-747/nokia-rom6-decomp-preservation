; ROM6 0x38FB FRAG_38FB -- 11w, symbols.yaml data_word.
; Evidence: Bound 38FB-3905 (11w; exit retd FE00@3902 + delays 3903-3904 included per convention; or #0,a operand word 3905 homed here, overlap-corrected wave-12; exit scan clean); entries cc F930@38AE->38FB byte-verified (cond call from FRAG_389C interior)
; ORIGIN 0x38FB
	.sect ".text"
	.mmregs
	.global _start
_start:
	sfta   a,2,b
	and    #252,b
	or     #3,b
	sfta   a,3
	and    #-512,a
	or     b,a
	or     #0,a
