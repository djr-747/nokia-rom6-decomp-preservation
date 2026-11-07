; ROM6 0xD39E LEAF_D39E -- 32w, symbols.yaml data_word.
; Evidence: Entry 7713 3161 EC04 E589 7713 3161 7717 0002; callers D3D4/D49D calld; first-RET FC00 @D3BD (32w); RPT#4/RPTBD, zero subcalls/ports; HYPOTHESIS param-loop leaf.
; ORIGIN 0xD39E
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #12641,ar3
	rpt    #4
	mvdd   *ar2+,*ar3+
	stm    #12641,ar3
	stm    #2,ar7
	stm    #-16384,t
	stm    #16,ar4
	mvmm   ar3,ar6
	stm    #4,brc
	ld     *ar6,16,a
	rptbd  0xd3b6
	ld     #-8192,16,b
	sub    b,a
	srccd  *ar4,ageq
	ld     *ar6+,16,a
	max    b
	ld     *ar6,16,a
	addm   #1,*ar4
	banzd  0xd3aa,*ar7-
	mar    *ar6-0
	st     t,*ar6
	ret
