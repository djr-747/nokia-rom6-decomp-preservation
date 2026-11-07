; ROM6 0x8907 FRAG_8907 -- 21w, symbols.yaml program_word.
; Evidence: Bound 8907-891B (21w = full gap); entry TRACE (same histogram: 8907-891B heads x3, rptbd body 8913-8914 x12); bitf/brc repeat-minmax leaf (bitf/xc/ld/rptbd/min/stl/bitf/bc/orm); ab
; ORIGIN 0x8907
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x577),#-32768
	stm    #3,brc
	ld     #2,b
	xc     1,ntc
	ld     #3,b
	rptbd  0x8915
	stm    #12082,ar2
	ld     *ar2,a
	min    a
	stl    a,*ar2+
	bitf   *ar4,#1
	bc     0x8936,tc
	orm    #1,*ar4
