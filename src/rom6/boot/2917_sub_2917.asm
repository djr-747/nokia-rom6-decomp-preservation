; ROM6 0x2917 SUB_2917 -- 54w, symbols.yaml program_word.
; Evidence: Bound 2917-294C (38w); entry TRACE (same histogram: 2917-294B heads x10681, rare 291C lane x37); interior b-joins 292C/30/36/38/46->294B (mesh joins, kept); exits b F073@294B->283D
; ORIGIN 0x2917
	.sect ".text"
	.global _start
_start:
	cmpm   *(0x2656),#0
	bc     0x291e,tc
	call   0x3aed
	cmpm   *(0x250f),#34
	bc     0x2929,ntc
	st     #0,*(0x366f)
	st     #0,*(0x37b0)
	st     #0,*(0x2656)
	b      0x294b
	call   0xa5f2
	b      0x294b
	call   0xa615
	call   0xa639
	b      0x294b
	b      0x294b
	bd     0x2940
	stm    #13458,ar1
	stm    #13457,ar1
	ld     *ar1,16,a
	bitf   *(0x3ec8),#32
	cc     0x3cd2,ntc
	b      0x294b
	andm   #-513,*(0x2639)
	b      0x283d
