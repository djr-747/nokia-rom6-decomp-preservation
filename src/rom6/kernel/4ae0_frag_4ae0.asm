; ROM6 0x4AE0 FRAG_4AE0 -- 19w, symbols.yaml data_word.
; Evidence: Bound 4AE0-4AF2 (19w; exit B F073@4AF1->4ADF + operand 4AF2 — branch-tailed, tail-shares FRAG_4ADF RET; exit scan otherwise clean); entry BD F273@4A5F->4AE0 byte-verified (delayed 
; ORIGIN 0x4AE0
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar5,b
	call   0x4590
	st     #0,*(0x2656)
	cmpm   *(0x250f),#34
	bc     0x4adf,ntc
	st     #0,*(0x366f)
	st     #0,*(0x37b0)
	b      0x4adf
