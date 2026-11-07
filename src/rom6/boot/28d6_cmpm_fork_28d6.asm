; ROM6 0x28D6 CMPM_FORK_28D6 -- 65w, symbols.yaml program_word.
; Evidence: Post-head (prev 28cf span); cmpm/bc fork ladder with xc-or lanes, stm/or/b tails rejoining the 291C join; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x28D6
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x34bf),#1
	bc     0x2910,tc
	cmpm   *(0x34bf),#4
	bc     0x2910,tc
	cmpm   *(0x34bf),#3
	bc     0x2909,ntc
	cmpm   *(0x366f),#0
	ld     #0,a
	nop
	xc     2,tc
	or     #1,a
	cmpm   *(0x37b0),#0
	nop
	nop
	xc     2,tc
	or     #2,a
	bc     0x291c,aeq
	sub    #2,a
	bc     0x2902,alt
	bc     0x291e,agt
	orm    #512,*(0x3490)
	b      0x291c
	stm    #1170,ar2
	orm    #256,*(0x3490)
	b      0x291c
	cmpm   *(0x366f),#0
	bc     0x291e,tc
	b      0x291c
	cmpm   *(0x37b0),#0
	bc     0x291e,tc
	b      0x291c
