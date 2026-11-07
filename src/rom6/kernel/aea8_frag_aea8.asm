; ROM6 0xAEA8 FRAG_AEA8 -- 5w, symbols.yaml program_word.
; Evidence: Bound AEA8-AEAC (5w); entry TRACE (same histogram: AEA8-AC heads x10682); stm/mvdd/mvdd/ret leaf; refutes post-retd-orphan kill (reached via computed path); HYPOTHESIS.
; ORIGIN 0xAEA8
	.sect ".text"
	.global _start
_start:
	stm    #16122,ar3
	mvdd   *ar3+,*ar2+
	mvdd   *ar3+,*ar2+
	ret
