; ROM6 0x89B3 FRAG_89B3 -- 17w, symbols.yaml data_word.
; Evidence: Bound 89B3-89C3 (17w; exit B F073@89C2->8894 + operand 89C3, byte-verified (8894 = FRAG_8894 head, CODE — its note already counts this B as entry); exit scan clean); entries bc F84
; ORIGIN 0x89B3
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #6,*(0x55a)
	stm    #12432,ar2
	rpt    #24
	mvkd   0xb373,*ar2+
	stm    #2,brc
	rptb   0x89c1
	rpt    #16
	mvkd   0xb37b,*ar2+
	b      0x8894
