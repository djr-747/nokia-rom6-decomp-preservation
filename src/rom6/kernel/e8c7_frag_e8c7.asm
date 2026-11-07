; ROM6 0xE8C7 FRAG_E8C7 -- 29w, symbols.yaml data_word.
; Evidence: Bound E8C7-E8E3 (29w; sole exit RET FC00@E8E3 byte-verified); entry F074 call @E93F (byte-verified); prologue opaque A301 A001 8783 (pre F5E6 unresolved, noted); interior join B@E8
; ORIGIN 0xE8C7
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    *ar2,*ar3,b
	add    *ar2,*ar3,a
	sth    b,asm,*ar3
	add    *ar4,*ar5,b
	add    b,a
	sth    a,asm,*ar2+
	sub    b,1,a
	sub    *ar4,*ar5,b
	st     a,*ar4+ || ld     *ar3,a
	sth    b,asm,*ar5+
	sub    *ar4,*ar5-,b
	add    b,asm,a
	sth    a,*ar3+
	sub    b,-1,a
	ld     *ar5,16,b
	sth    a,*ar5+
	add    *ar4,*ar5,a
	sth    a,asm,*ar4
	sub    *ar2,*ar3,a
	add    b,2,a
	sth    a,asm,*ar5+0
	sub    b,3,a
	add    *ar2,*ar3,b
	st     a,*ar3+0% || ld     *ar4,a
	add    a,2,b
	sth    b,asm,*ar2+0
	sub    a,3,b
	sth    b,asm,*ar4+0
	ret
