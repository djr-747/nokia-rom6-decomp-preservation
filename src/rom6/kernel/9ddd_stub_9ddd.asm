; ROM6 0x9DDD STUB_9DDD -- 23w, symbols.yaml data_word.
; Evidence: Entry F074 06C0 76F8 057D 2900 76F8 057E; caller F074@E7F1 (objdump call); first-RET @0x9DF3 (23w); HYPOTHESIS.
; ORIGIN 0x9DDD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6c0
	st     #10496,*(0x57d)
	st     #12854,*(0x57e)
	st     #12854,*(0x2a69)
	st     #0,*(0x57c)
	st     #0,*(0x861)
	stm    #12854,ar1
	ld     #0,a
	rpt    #159
	stl    a,*ar1+
	ret
