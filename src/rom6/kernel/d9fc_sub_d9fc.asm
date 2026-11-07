; ROM6 0xD9FC SUB_D9FC -- 26w, symbols.yaml data_word.
; Evidence: Entry 7712 0A5E E807 8092; first exit retd FE00 @DA15 entry-linear; Bound DA16-DA17 (RETD@DA15 delay slots — wave-11 spill fix); caller F274 @D9BF verified; HYPOTHESIS.
; ORIGIN 0xD9FC
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2654,ar2
	ld     #7,a
	stl    a,*ar2+
	st     #32767,*ar2+
	st     #1,*ar2+
	st     #23,*ar2+
	sth    a,*ar2+
	sth    a,*ar2+
	st     #28801,*ar2+
	st     #26968,*ar2+
	stm    #6,brc
	rptbd  0xda14
	stm    #2766,ar2
	rpt    #9
	mvpd   0xd9c9,*ar2+
	retd
