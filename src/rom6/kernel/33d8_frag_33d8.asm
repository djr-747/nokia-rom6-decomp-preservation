; ROM6 0x33D8 FRAG_33D8 -- 16w, symbols.yaml data_word.
; Evidence: Bound 33D8-33E7 (16w; exit F073@33E6->2E64 + operand 33E7); post-ret entry (FC00@33D7); zero refs/callers; head 69F8/054F/0040 + 2A86-lane; interior F074-call 2E2F@33E4 (slice-veri
; ORIGIN 0x33D8
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #64,*(0x54f)
	stm    #10886,ar3
	rpt    #39
	mvdd   *ar2+0%,*ar3+
	orm    #-1,*ar3
	st     #10886,*(0x2a84)
	call   0x2e2f
	b      0x2e64
