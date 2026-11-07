; ROM6 0xAB56 PRED_AB56 -- 34w, symbols.yaml data_word.
; Evidence: Entry F3F0 F820 AB76 8914 1083 8812 (branch-entered); bound AB56-AB77 (FC00@AB77, adjacent AB78); callers F274 @AB48/AB51 (interior to AB2C); zero interior calls; cond bc AB76 ntc 
; ORIGIN 0xAB56
	.sect ".text"
	.mmregs
	.global _start
_start:
	sftl   b,-16
	bc     0xab76,ntc
	stlm   b,ar4
	ld     *ar3,a
	stlm   a,ar2
	sub    *ar3,b
	abs    b,a
	mvmm   ar2,ar5
	sub    #150,a
	bc     0xab67,alt
	ldm    bk,a
	xc     1,bgt
	neg    a
	add    a,b
	abs    b,a
	sub    #1,a
	rc     aleq
	xc     1,bgt
	mar    *ar2+%
	xc     1,bgt, bov
	mvdd   *ar5,*ar2
	sub    #3,a
	xc     1,blt
	mar    *ar2-%
	xc     1,agt
	mvmm   ar4,ar2
	ldm    ar2,b
	stl    b,*ar3
	ret
