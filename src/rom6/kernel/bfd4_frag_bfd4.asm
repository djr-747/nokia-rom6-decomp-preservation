; ROM6 0xBFD4 FRAG_BFD4 -- 10w, symbols.yaml data_word.
; Evidence: Bound BFD4-BFDD (10w; exit RETD FE00@BFDB + delays BFDC-BFDD (sth/strcd 2w), byte-verified; exit scan clean); entry bc F84D@BFC9->BFD4 byte-verified (cond beq, chained from FRAG_BF
; Pool: SQUR square + MAS subtract + STRCD conditional store + ADDS (all oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xBFD4
	.sect ".text"
	.mmregs
	.global _start
_start:
	mpya   *ar1
	adds   0x42,b
	sth    b,0x68
	squr   0x68,a
	sub    *ar2,15,a
	mas    0x41,a
	sub    0x41,16,b
	retd
	sth    b,*ar2
	strcd  *ar2,alt
