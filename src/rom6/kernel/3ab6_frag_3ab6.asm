; ROM6 0x3AB6 FRAG_3AB6 -- 40w, symbols.yaml data_word.
; Evidence: Bound 3AB6-3ADD (40w; exit RET FC00@3ADD byte-verified, exit scan clean); post-RET head (FC00@3AB5 = FRAG_3A8E exit, CODE); sole exterior ref calld F274@8085->3AB6 is dark-src (unc
; ORIGIN 0x3AB6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x632
	call   0x3ade
	ssbx   st1,intm
	portr  0,*(0x8)
	and    #-97,a
	nop
	portw  *(0x8),0
	rpt    #20
	nop
	rsbx   st1,intm
	ld     #3,a
	nop
	portw  *(0x8),60
	ld     #7,a
	nop
	portw  *(0x8),60
	stm    #2,brc
	rptb   0x3ad7
	portr  57,*ar2+
	nop
	ld     #2,a
	nop
	portw  *(0x8),60
	ret
