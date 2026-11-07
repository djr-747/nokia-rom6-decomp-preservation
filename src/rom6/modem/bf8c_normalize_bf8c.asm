; ROM6 0xBF8C NORMALIZE_BF8C -- 30w, symbols.yaml data_word.
; Evidence: Entry F074 06DE; exp/norm/sat + subc-divide + DP+0x41/0x42/0x43 scale; first-RET @0xBFA9 (len 30); 4 callers BD5D C057 C31F C49A-calld; HYPOTHESIS normalize/scale.
; ORIGIN 0xBF8C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6de
	rcd    aeq
	sth    a,*ar1+
	sth    a,*ar1-
	pshm   st1
	rsbx   st1,ovm
	abs    a,b
	exp    b
	rsbx   st1,sxm
	norm   b
	adds   0x42,b
	sat    b
	sth    b,*ar1
	ld     0x43,16,b
	rpt    #15
	subc   *ar1,b
	and    #-1,b
	add    0x41,b
	ld     b,15,b
	xc     1,alt
	neg    b
	sat    b
	sth    b,*ar1+
	st     t,*ar1
	addm   #-30,*ar1-
	popm   st1
	ret
