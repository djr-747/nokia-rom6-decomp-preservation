; ROM6 0x3557 FRAG_3557 -- 5w, symbols.yaml program_word.
; Evidence: Bound 3557-355B (5w); entry TRACE (same histogram: 3557/355A x2); bitf/bc 35A0 lane head (not-taken lane 355C+ dead); HYPOTHESIS.
; ORIGIN 0x3557
	.sect ".text"
	.global _start
_start:
	bitf   *(0x3ec8),#512
	bc     0x35a0,ntc
