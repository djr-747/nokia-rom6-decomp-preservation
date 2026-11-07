; ROM6 0x802D FRAG_802D -- 82w, symbols.yaml data_word.
; Evidence: Bound 802D-807E (82w; exit RET FC00@807E byte-verified; interior join BD F273@8034->804D; exit scan otherwise clean); entries branch-only: bc F830@7C92->8038 + F844@7FF8->805A + bc
; ORIGIN 0x802D
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @802D 1bf8 or     *(0x34b1),b
	or     *(0x34b1),b
	; @802F 8184 stl    b,*ar4
	stl    b,*ar4
	; @8030 f274 calld  0x807f
	calld  0x807f
	; @8032 7713 stm    #9687,ar3
	stm    #9687,ar3
	; @8034 f273 bd     0x804d
	bd     0x804d
	; @8036 7712 stm    #9701,ar2
	stm    #9701,ar2
	; @8038 f074 call   0x59e
	call   0x59e
	; @803A 10f8 ld     *(0x2650),a
	ld     *(0x2650),a
	; @803C f844 bc     0x805a,aneq
	bc     0x805a,aneq
	; @803E 10f8 ld     *(0x25c1),a
	ld     *(0x25c1),a
	; @8040 e905 ld     #5,b
	ld     #5,b
	; @8041 f945 cc     0x4590,aeq
	cc     0x4590,aeq
	; @8043 7714 stm    #9665,ar4
	stm    #9665,ar4
	; @8045 7694 st     #0,*ar4+
	st     #0,*ar4+
	; @8047 f274 calld  0x807f
	calld  0x807f
	; @8049 7713 stm    #9666,ar3
	stm    #9666,ar3
	; @804B 7712 stm    #9680,ar2
	stm    #9680,ar2
	; @804D 7711 stm    #14,ar1
	stm    #14,ar1
	; @804F 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @8052 f820 bc     0x8056,ntc
	bc     0x8056,ntc
	; @8054 7682 st     #0,*ar2
	st     #0,*ar2
	; @8056 f274 calld  0x7fdc
	calld  0x7fdc
	; @8058 7713 stm    #1110,ar3
	stm    #1110,ar3
	; @805A e804 ld     #4,a
	ld     #4,a
	; @805B 00f8 add    *(0x2650),a
	add    *(0x2650),a
	; @805D 8860 stlm   a,96
	stlm   a,96
	; @805E 7712 stm    #10884,ar2
	stm    #10884,ar2
	; @8060 771a stm    #29,brc
	stm    #29,brc
	; @8062 7713 stm    #1110,ar3
	stm    #1110,ar3
	; @8064 e800 ld     #0,a
	ld     #0,a
	; @8065 f272 rptbd  0x806d
	rptbd  0x806d
	; @8067 7714 stm    #12091,ar4
	stm    #12091,ar4
	; @8069 1a8b or     *ar3-,a
	or     *ar3-,a
	; @806A f468 sfta   a,8
	sfta   a,8
	; @806B 828c sth    a,*ar4-
	sth    a,*ar4-
	; @806C f468 sfta   a,8
	sfta   a,8
	; @806D 828c sth    a,*ar4-
	sth    a,*ar4-
	; @806E 7710 stm    #12032,ar0
	stm    #12032,ar0
	; @8070 f274 calld  0x7eb3
	calld  0x7eb3
	; @8072 10f8 ld     *(0x60),a
	ld     *(0x60),a
	; @8074 f274 calld  0x7fc6
	calld  0x7fc6
	; @8076 7712 stm    #10884,ar2
	stm    #10884,ar2
	; @8078 6982 orm    #1536,*ar2
	orm    #1536,*ar2
	; @807A f274 calld  0x7c9e
	calld  0x7c9e
	; @807C 7712 stm    #9808,ar2
	stm    #9808,ar2
	; @807E fc00 ret
	ret
