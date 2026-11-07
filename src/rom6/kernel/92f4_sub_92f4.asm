; ROM6 0x92F4 SUB_92F4 -- 33w, symbols.yaml data_word.
; Evidence: Bound 92F4-9314 (33w; exit RET FC00@9314); entry F074 0676 (objdump call); caller F274@0x4C69 byte- verified; interior calls 9233/90B9/90D6/90E7/9331 (9233 = backward frag call, 93
; ORIGIN 0x92F4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x676
	call   0x9233
	stm    #78,ar1
	call   0x90b9
	stm    #12608,ar1
	st     #15,*(0x61)
	call   0x90d6
	st     #2,*(0x61)
	call   0x90e7
	st     #5,*(0x61)
	call   0x90d6
	call   0x9331
	sftl   a,14
	stl    a,*ar3
	rpt    #6
	mvdk   *ar3+,0x2f80
	ret
