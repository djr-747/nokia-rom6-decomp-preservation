; ROM6 0x9315 SPAN_TAIL_9315 -- 28w, symbols.yaml data_word.
; Evidence: Entry F074 0594 7714 B405 E800 7710 0000 7711; first-RET @0x9330 (len 28); 6 callers 9260 927C 9295 92B2 92CF 92EB (all F074); span tail into 0x938C; HYPOTHESIS leaf.
; ORIGIN 0x9315
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	stm    #-19451,ar4
	ld     #0,a
	stm    #0,ar0
	stm    #31,ar1
	mvdm   0x60,ar3
	mar    *ar6-
	rptb   0x932f
	ld     *ar4+0,t
	bitt   *ar6-
	roltc  a
	and    #15,a,b
	stlm   b,ar0
	banz   0x932f,*ar1-
	sth    a,*ar3-
	stl    a,*ar3-
	stm    #31,ar1
	mar    *ar4-0
	ret
