; ROM6 0x5A68 FRAG_5A68 -- 68w, symbols.yaml data_word.
; Evidence: Bound 5A68-5AAB (68w; exit RET FC00@5AAB byte-verified, exit scan clean); post-RET head only (FC00@5A67, zero exterior refs — thin entry, head out-call F074@5A68->059C corroborates
; ORIGIN 0x5A68
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #2508,bk
	mpy    *(0x264c),#114,a
	stlm   a,ar0
	stm    #3,ar6
	stm    #5,ar5
	stm    #0,ar4
	mvmm   ar4,ar1
	stm    #18,brc
	rptb   0x5a9e
	mvmm   ar1,ar3
	cmpm   *(0x250f),#34
	bc     0x5a86,ntc
	ld     *(0x352c),2,a
	b      0x5a88
	ld     #11036,2,a
	mar    *ar3+0%
	add    *(0x13),a
	and    #3,a,b
	mpy    *(0xb),#-4,b
	stlm   b,t
	sfta   a,-2
	stlm   a,ar3
	stm    #2185,bk
	ld     *ar3,ts,a
	and    #15,a
	stl    a,*ar2
	mar    *+ar1(0x2b2)%
	stm    #2508,bk
	mar    *+ar2(0x6)
	mar    *+ar2(0xff8f)
	banzd  0x5a76,*ar5-
	mar    *+ar4(0x86)
	mar    *+ar0(0x72)
	banzd  0x5a72,*ar6-
	mar    *+ar2(0x6c)
	ret
