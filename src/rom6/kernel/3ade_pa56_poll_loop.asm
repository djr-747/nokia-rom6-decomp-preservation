; ROM6 0x3ADE PA56_POLL_LOOP -- 15w, symbols.yaml data_word.
; Evidence: Entry F074 0632; bound 3ADE-3AEC; callers F074@39F7/3A83/3AB8; pa56 poll self-loop bc 3AE5->3ADE; HYPOTHESIS.
; ORIGIN 0x3ADE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x632
	portr  56,*(0x8)
	and    #128,a
	bc     0x3ade,aneq
	portr  56,*(0x8)
	and    #96,a
	ret
