; ROM6 0x8F20 LEAF_8F20 -- 90w, symbols.yaml data_word.
; Evidence: Bound 8F20-8F79 (FC00@8F79); entry is bd-target of F273@8F18 (inside WORKER_8E88 span); head 4543 4321 8343 F020; zero calls; HYPOTHESIS bd-target leaf.
; ORIGIN 0x8F20
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     0x43,16,b
	sub    0x21,16,b
	sth    b,0x43
	ld     #-19482,a
	add    b,-16,a
	stlm   a,ar2
	ld     #6,a
	sub    0x42,a
	ld     *ar2,t
	stl    a,0x46
	ld     0x46,asm
	stm    #12071,ar2
	stm    #12,brc
	rptbd  0x8f39
	st     #4,0x21
	ld     *ar2,16,b
	ld     b,asm,a
	mpya   a
	ld     0x21,16,b
	add    a,-12,b
	sth    b,*ar2+
	rpt    #16
	mvkd   0x2f23,*ar5+
	rptz   a,#39
	mvmd   al,0x2f50
	ld     #-19474,a
	add    0x43,a
	stlm   a,ar2
	ld     0x46,a
	sub    0x20,a
	mvdk   *ar2,0x2f45
	stl    a,0x21
	ld     0x21,t
	ld     0x20,ts,a
	stl    a,0x47
	ld     #12112,a
	add    0x25,a
	stlm   a,ar2
	stm    #3,ar0
	ld     0x46,a
	neg    a
	stl    a,0x46
	ld     0x46,asm
	ld     0x44,a
	ld     0x47,16,b
	stm    #0,bk
	stm    #12103,ar4
	stm    #12,brc
	rptbd  0x8f68
	stm    #12071,ar3
	add    *ar3+,1,a
	sfta   a,13
	sfta   a,15
	macar  0x45,b
	ld     0x44,a
	st     b,*ar2+0% || ld     *ar4,b
	stm    #4116,ar2
	rpt    #79
	mvkd   0x103c,*ar2+
	stm    #12112,ar3
	stm    #39,brc
	rptbd  0x8f77
	stm    #12157,ar4
	add    *ar3+,*ar4+,a
	sth    a,*ar2+
	ld     #0,asm
	ret
