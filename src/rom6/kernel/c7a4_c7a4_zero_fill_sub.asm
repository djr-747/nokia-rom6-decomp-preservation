; ROM6 0xC7A4 C7A4_ZERO_FILL_SUB -- 13w, symbols.yaml data_word.
; Evidence: Post-ret-ret head (FC00 @C7A2/C7A3 precede); entry F074 0694 then zero-fill stm/rptz/mvkd lanes; first exit ret FC00 @C7B0 entry-linear; zero F074/F274 callers image-wide; CALLERLE
; ORIGIN 0xC7A4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x694
	stm    #10393,ar2
	rptz   a,#23
	stl    a,*ar2+
	stm    #10417,ar2
	rpt    #30
	mvkd   0xb609,*ar2+
	ret
