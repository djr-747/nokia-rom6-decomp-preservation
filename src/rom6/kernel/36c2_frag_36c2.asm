; ROM6 0x36C2 FRAG_36C2 -- 31w, symbols.yaml data_word.
; Evidence: Bound 36C2-36E0 (31w; exit B F073@36DF->2E64 + operand 36E0, byte-verified; exit scan clean); entries 2x bc F830@36A9->36C2 (tc) + F820@36AE->36C2 (ntc) byte-verified (both exterio
; ORIGIN 0x36C2
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2+%,a
	cmpm   *(0x8),#1
	bc     0x36e1,ntc
	st     #1,*(0x58f)
	mvdk   *ar2+%,0x27fe
	mvdk   *ar2+%,0x27ff
	mvdk   *ar2+%,0x2940
	mvdk   *ar2+%,0x2941
	mvdk   *ar2+%,0x2979
	mvdk   *ar2+%,0x244f
	mvdk   *ar2+%,0x2450
	call   0x2e2f
	call   0xe79d
	call   0xe7ef
	b      0x2e64
