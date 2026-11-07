; ROM6 0x6B26 SPANHEAD_6B26 -- 1107w, symbols.yaml data_word.
; Evidence: Fallthrough 6B25 + ext F820@6AFE entry; bound 6B26-6F78 (FC00); bytes 60F8/250F/0022 cmpm + 3490 bitf; sites F074 05A2@6B63, 712Dx3, 05AA@6C27, 7142x2, 7067@6C6E, 7167x2+F274, call
; ORIGIN 0x6B26
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @6B26 61f8 bitf   *(0x534),#1
	bitf   *(0x534),#1
	; @6B29 6881 andm   #-769,*ar1
	andm   #-769,*ar1
	.word 0xFF30 ; XC: gas encoder gap
	; @6B2C 6981 orm    #256,*ar1
	orm    #256,*ar1
	; @6B2E 60f8 cmpm   *(0x262a),#128
	cmpm   *(0x262a),#128
	; @6B31 f830 bc     0x6b3d,tc
	bc     0x6b3d,tc
	; @6B33 60f8 cmpm   *(0x262a),#112
	cmpm   *(0x262a),#112
	; @6B36 f830 bc     0x6b3d,tc
	bc     0x6b3d,tc
	; @6B38 61f8 bitf   *(0x2628),#4
	bitf   *(0x2628),#4
	; @6B3B f820 bc     0x6b3f,ntc
	bc     0x6b3f,ntc
	; @6B3D 6981 orm    #512,*ar1
	orm    #512,*ar1
	; @6B3F 5682 dld    *ar2,a
	dld    *ar2,a
	; @6B40 6d94 mar    *ar4+
	mar    *ar4+
	; @6B41 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6B44 e907 ld     #7,b
	ld     #7,b
	; @6B45 19f8 and    *(0x3490),b
	and    *(0x3490),b
	; @6B47 f310 sub    #1,b
	sub    #1,b
	; @6B49 f820 bc     0x6b51,ntc
	bc     0x6b51,ntc
	.word 0xFF4D ; XC: gas encoder gap
	; @6B4C 7714 stm    #13494,ar4
	stm    #13494,ar4
	.word 0xFF4E ; XC: gas encoder gap
	; @6B4F 7714 stm    #13496,ar4
	stm    #13496,ar4
	; @6B51 e900 ld     #0,b
	ld     #0,b
	; @6B52 8194 stl    b,*ar4+
	stl    b,*ar4+
	; @6B53 8184 stl    b,*ar4
	stl    b,*ar4
	; @6B54 61f8 bitf   *(0x2628),#32
	bitf   *(0x2628),#32
	; @6B57 fa20 bcd    0x6e96,ntc
	bcd    0x6e96,ntc
	; @6B59 7713 stm    #9785,ar3
	stm    #9785,ar3
	; @6B5B 61f8 bitf   *(0x263a),#2048
	bitf   *(0x263a),#2048
	; @6B5E f830 bc     0x6b63,tc
	bc     0x6b63,tc
	; @6B60 68f8 andm   #-4097,*(0x263a)
	andm   #-4097,*(0x263a)
	; @6B63 f074 call   0x5a2
	call   0x5a2
	; @6B65 11f8 ld     *(0x533),b
	ld     *(0x533),b
	; @6B67 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6B6A f820 bc     0x6b7a,ntc
	bc     0x6b7a,ntc
	; @6B6C 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6B6F f820 bc     0x6b73,ntc
	bc     0x6b73,ntc
	; @6B71 11f8 ld     *(0x37f6),b
	ld     *(0x37f6),b
	; @6B73 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6B76 f820 bc     0x6b7a,ntc
	bc     0x6b7a,ntc
	; @6B78 11f8 ld     *(0x37f7),b
	ld     *(0x37f7),b
	; @6B7A 6183 bitf   *ar3,#32
	bitf   *ar3,#32
	; @6B7C fa30 bcd    0x6b8e,tc
	bcd    0x6b8e,tc
	; @6B7E 7714 stm    #9308,ar4
	stm    #9308,ar4
	; @6B80 8184 stl    b,*ar4
	stl    b,*ar4
	; @6B81 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6B84 f820 bc     0x6b8a,ntc
	bc     0x6b8a,ntc
	; @6B86 f074 call   0x712d
	call   0x712d
	; @6B88 f820 bc     0x6b8c,ntc
	bc     0x6b8c,ntc
	; @6B8A 6983 orm    #32,*ar3
	orm    #32,*ar3
	; @6B8C f073 b      0x6c0b
	b      0x6c0b
	; @6B8E 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6B91 f820 bc     0x6b97,ntc
	bc     0x6b97,ntc
	; @6B93 f074 call   0x712d
	call   0x712d
	; @6B95 f820 bc     0x6b99,ntc
	bc     0x6b99,ntc
	; @6B97 6883 andm   #-33,*ar3
	andm   #-33,*ar3
	; @6B99 7692 st     #0,*ar2+
	st     #0,*ar2+
	; @6B9B 7682 st     #0,*ar2
	st     #0,*ar2
	; @6B9D 0184 add    *ar4,b
	add    *ar4,b
	; @6B9E 8915 stlm   b,ar5
	stlm   b,ar5
	; @6B9F 7684 st     #0,*ar4
	st     #0,*ar4
	; @6BA1 7714 stm    #21,ar4
	stm    #21,ar4
	; @6BA3 6084 cmpm   *ar4,#0
	cmpm   *ar4,#0
	; @6BA5 f830 bc     0x6c0b,tc
	bc     0x6c0b,tc
	; @6BA7 f274 calld  0x4384
	calld  0x4384
	; @6BA9 7712 stm    #12032,ar2
	stm    #12032,ar2
	; @6BAB f640 ld     b,a
	ld     b,a
	; @6BAC f074 call   0x4315
	call   0x4315
	; @6BAE 61f8 bitf   *(0x3ec8),#32
	bitf   *(0x3ec8),#32
	; @6BB1 f820 bc     0x6be9,ntc
	bc     0x6be9,ntc
	; @6BB3 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6BB6 fa20 bcd    0x6bc8,ntc
	bcd    0x6bc8,ntc
	; @6BB8 7712 stm    #9360,ar2
	stm    #9360,ar2
	; @6BBA 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6BBD f820 bc     0x6bc1,ntc
	bc     0x6bc1,ntc
	; @6BBF 7712 stm    #13457,ar2
	stm    #13457,ar2
	; @6BC1 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6BC4 f820 bc     0x6bc8,ntc
	bc     0x6bc8,ntc
	; @6BC6 7712 stm    #13458,ar2
	stm    #13458,ar2
	; @6BC8 4a08 pshm   al
	pshm   al
	; @6BC9 4a09 pshm   ah
	pshm   ah
	; @6BCA 4a0a pshm   ag
	pshm   ag
	; @6BCB 11f8 ld     *(0x2611),b
	ld     *(0x2611),b
	; @6BCD f210 sub    #124,b,a
	sub    #124,b,a
	; @6BCF fa47 bcd    0x6bd9,aleq
	bcd    0x6bd9,aleq
	; @6BD1 f020 ld     #1140,a
	ld     #1140,a
	; @6BD3 f310 sub    #975,b
	sub    #975,b
	; @6BD5 f84a bc     0x6bd9,bgeq
	bc     0x6bd9,bgeq
	; @6BD7 f020 ld     #1180,a
	ld     #1180,a
	; @6BD9 6f82 add    *ar2,a,b
	add    *ar2,a,b
	; @6BDB 8a0a popm   ag
	popm   ag
	; @6BDC 8a09 popm   ah
	popm   ah
	; @6BDD 8a08 popm   al
	popm   al
	; @6BDE 8913 stlm   b,ar3
	stlm   b,ar3
	; @6BDF 40f8 sub    *(0x3e97),16,a
	sub    *(0x3e97),16,a
	; @6BE1 f484 neg    a
	neg    a
	; @6BE2 3c83 add    *ar3,16,a
	add    *ar3,16,a
	; @6BE3 f470 sfta   a,-16
	sfta   a,-16
	; @6BE4 f074 call   0x6fb1
	call   0x6fb1
	; @6BE6 8082 stl    a,*ar2
	stl    a,*ar2
	; @6BE7 f073 b      0x6c0b
	b      0x6c0b
	; @6BE9 f47a sfta   a,-6
	sfta   a,-6
	; @6BEA f001 add    #16384,1,a
	add    #16384,1,a
	; @6BEC 76f8 st     #0,*(0x8)
	st     #0,*(0x8)
	; @6BEF 7713 stm    #9360,ar3
	stm    #9360,ar3
	; @6BF1 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6BF4 f820 bc     0x6c04,ntc
	bc     0x6c04,ntc
	; @6BF6 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6BF9 f820 bc     0x6bfd,ntc
	bc     0x6bfd,ntc
	; @6BFB 7713 stm    #13457,ar3
	stm    #13457,ar3
	; @6BFD 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6C00 f820 bc     0x6c04,ntc
	bc     0x6c04,ntc
	; @6C02 7713 stm    #13458,ar3
	stm    #13458,ar3
	; @6C04 40f8 sub    *(0x3e97),16,a
	sub    *(0x3e97),16,a
	; @6C06 f484 neg    a
	neg    a
	; @6C07 3c83 add    *ar3,16,a
	add    *ar3,16,a
	; @6C08 f074 call   0x6f88
	call   0x6f88
	; @6C0A 8083 stl    a,*ar3
	stl    a,*ar3
	; @6C0B 7714 stm    #9767,ar4
	stm    #9767,ar4
	; @6C0D 7712 stm    #9806,ar2
	stm    #9806,ar2
	; @6C0F 6182 bitf   *ar2,#1
	bitf   *ar2,#1
	; @6C11 fa20 bcd    0x6c4f,ntc
	bcd    0x6c4f,ntc
	; @6C13 1182 ld     *ar2,b
	ld     *ar2,b
	; @6C14 1084 ld     *ar4,a
	ld     *ar4,a
	; @6C15 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C18 f820 bc     0x6c1e,ntc
	bc     0x6c1e,ntc
	; @6C1A f074 call   0x712d
	call   0x712d
	; @6C1C f820 bc     0x6c20,ntc
	bc     0x6c20,ntc
	; @6C1E f350 xor    #1,b
	xor    #1,b
	; @6C20 8182 stl    b,*ar2
	stl    b,*ar2
	; @6C21 f030 and    #32767,a
	and    #32767,a
	; @6C23 8084 stl    a,*ar4
	stl    a,*ar4
	; @6C24 e800 ld     #0,a
	ld     #0,a
	; @6C25 7712 stm    #9340,ar2
	stm    #9340,ar2
	; @6C27 f074 call   0x5aa
	call   0x5aa
	; @6C29 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C2C f820 bc     0x6c30,ntc
	bc     0x6c30,ntc
	; @6C2E f074 call   0x7142
	call   0x7142
	; @6C30 ec03 rpt    #3
	rpt    #3
	; @6C31 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6C32 7712 stm    #9352,ar2
	stm    #9352,ar2
	; @6C34 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C37 f820 bc     0x6c3d,ntc
	bc     0x6c3d,ntc
	; @6C39 e801 ld     #1,a
	ld     #1,a
	; @6C3A f074 call   0x7142
	call   0x7142
	; @6C3C e800 ld     #0,a
	ld     #0,a
	; @6C3D ec05 rpt    #5
	rpt    #5
	; @6C3E 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6C3F 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C42 f830 bc     0x6c47,tc
	bc     0x6c47,tc
	; @6C44 76f8 st     #0,*(0x533)
	st     #0,*(0x533)
	; @6C47 7712 stm    #9364,ar2
	stm    #9364,ar2
	; @6C49 ec1f rpt    #31
	rpt    #31
	; @6C4A 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6C4B ec3f rpt    #63
	rpt    #63
	; @6C4C 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6C4D f073 b      0x6e96
	b      0x6e96
	; @6C4F 11f8 ld     *(0x2611),b
	ld     *(0x2611),b
	; @6C51 7713 stm    #16031,ar3
	stm    #16031,ar3
	; @6C53 7714 stm    #9352,ar4
	stm    #9352,ar4
	; @6C55 7712 stm    #9354,ar2
	stm    #9354,ar2
	; @6C57 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C5A f820 bc     0x6c6e,ntc
	bc     0x6c6e,ntc
	; @6C5C 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6C5F f820 bc     0x6c65,ntc
	bc     0x6c65,ntc
	; @6C61 7714 stm    #13438,ar4
	stm    #13438,ar4
	; @6C63 7712 stm    #13440,ar2
	stm    #13440,ar2
	; @6C65 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6C68 f820 bc     0x6c6e,ntc
	bc     0x6c6e,ntc
	; @6C6A 7714 stm    #13446,ar4
	stm    #13446,ar4
	; @6C6C 7712 stm    #13448,ar2
	stm    #13448,ar2
	; @6C6E f074 call   0x7067
	call   0x7067
	; @6C70 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C73 f820 bc     0x6c87,ntc
	bc     0x6c87,ntc
	; @6C75 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6C78 f820 bc     0x6c7e,ntc
	bc     0x6c7e,ntc
	; @6C7A 80f8 stl    a,*(0x34bc)
	stl    a,*(0x34bc)
	; @6C7C f073 b      0x6c89
	b      0x6c89
	; @6C7E 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6C81 f820 bc     0x6c87,ntc
	bc     0x6c87,ntc
	; @6C83 80f8 stl    a,*(0x34bd)
	stl    a,*(0x34bd)
	; @6C85 f073 b      0x6c89
	b      0x6c89
	; @6C87 80f8 stl    a,*(0x265d)
	stl    a,*(0x265d)
	; @6C89 7715 stm    #96,ar5
	stm    #96,ar5
	; @6C8B 7712 stm    #12039,ar2
	stm    #12039,ar2
	; @6C8D 9438 ld     *ar5,8,a
	ld     *ar5,8,a
	; @6C8E 1a85 or     *ar5,a
	or     *ar5,a
	; @6C8F 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6C92 f820 bc     0x6cad,ntc
	bc     0x6cad,ntc
	; @6C94 e907 ld     #7,b
	ld     #7,b
	; @6C95 19f8 and    *(0x3490),b
	and    *(0x3490),b
	; @6C97 f761 sfta   b,1
	sfta   b,1
	; @6C98 f300 add    #12039,b
	add    #12039,b
	; @6C9A 8912 stlm   b,ar2
	stlm   b,ar2
	; @6C9B e907 ld     #7,b
	ld     #7,b
	; @6C9C 19f8 and    *(0x3490),b
	and    *(0x3490),b
	; @6C9E 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6C9F f310 sub    #1,b
	sub    #1,b
	; @6CA1 7713 stm    #13527,ar3
	stm    #13527,ar3
	.word 0xFF4D ; XC: gas encoder gap
	; @6CA4 7713 stm    #13539,ar3
	stm    #13539,ar3
	.word 0xFF4E ; XC: gas encoder gap
	; @6CA7 7713 stm    #13551,ar3
	stm    #13551,ar3
	; @6CA9 f074 call   0x7167
	call   0x7167
	; @6CAB f073 b      0x6cb2
	b      0x6cb2
	; @6CAD 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6CAE f274 calld  0x7167
	calld  0x7167
	; @6CB0 7713 stm    #9341,ar3
	stm    #9341,ar3
	; @6CB2 f3a8 or     b,8
	or     b,8
	; @6CB3 8192 stl    b,*ar2+
	stl    b,*ar2+
	; @6CB4 7713 stm    #9343,ar3
	stm    #9343,ar3
	; @6CB6 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6CB9 f820 bc     0x6ccb,ntc
	bc     0x6ccb,ntc
	; @6CBB 7713 stm    #13529,ar3
	stm    #13529,ar3
	; @6CBD 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6CC0 f820 bc     0x6cc4,ntc
	bc     0x6cc4,ntc
	; @6CC2 7713 stm    #13541,ar3
	stm    #13541,ar3
	; @6CC4 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6CC7 f820 bc     0x6ccb,ntc
	bc     0x6ccb,ntc
	; @6CC9 7713 stm    #13553,ar3
	stm    #13553,ar3
	; @6CCB 60f8 cmpm   *(0x2510),#128
	cmpm   *(0x2510),#128
	; @6CCE f830 bc     0x6d22,tc
	bc     0x6d22,tc
	; @6CD0 60f8 cmpm   *(0x2510),#177
	cmpm   *(0x2510),#177
	; @6CD3 f830 bc     0x6d22,tc
	bc     0x6d22,tc
	; @6CD5 f074 call   0x7167
	call   0x7167
	; @6CD7 7713 stm    #12040,ar3
	stm    #12040,ar3
	; @6CD9 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6CDC f820 bc     0x6ce5,ntc
	bc     0x6ce5,ntc
	; @6CDE e807 ld     #7,a
	ld     #7,a
	; @6CDF 18f8 and    *(0x3490),a
	and    *(0x3490),a
	; @6CE1 f461 sfta   a,1
	sfta   a,1
	; @6CE2 f000 add    #12040,a
	add    #12040,a
	; @6CE4 8813 stlm   a,ar3
	stlm   a,ar3
	; @6CE5 f330 and    #255,b
	and    #255,b
	; @6CE7 6883 andm   #-256,*ar3
	andm   #-256,*ar3
	; @6CE9 1b83 or     *ar3,b
	or     *ar3,b
	; @6CEA 8183 stl    b,*ar3
	stl    b,*ar3
	; @6CEB 11f8 ld     *(0x2611),b
	ld     *(0x2611),b
	; @6CED 7713 stm    #16031,ar3
	stm    #16031,ar3
	; @6CEF 7714 stm    #9355,ar4
	stm    #9355,ar4
	; @6CF1 7712 stm    #9357,ar2
	stm    #9357,ar2
	; @6CF3 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6CF6 f820 bc     0x6d0a,ntc
	bc     0x6d0a,ntc
	; @6CF8 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6CFB f820 bc     0x6d01,ntc
	bc     0x6d01,ntc
	; @6CFD 7714 stm    #13441,ar4
	stm    #13441,ar4
	; @6CFF 7712 stm    #13443,ar2
	stm    #13443,ar2
	; @6D01 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6D04 f820 bc     0x6d0a,ntc
	bc     0x6d0a,ntc
	; @6D06 7714 stm    #13449,ar4
	stm    #13449,ar4
	; @6D08 7712 stm    #13451,ar2
	stm    #13451,ar2
	; @6D0A f074 call   0x7067
	call   0x7067
	; @6D0C 10f8 ld     *(0x60),a
	ld     *(0x60),a
	; @6D0E 7712 stm    #12039,ar2
	stm    #12039,ar2
	; @6D10 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D13 f820 bc     0x6d1c,ntc
	bc     0x6d1c,ntc
	; @6D15 e907 ld     #7,b
	ld     #7,b
	; @6D16 19f8 and    *(0x3490),b
	and    *(0x3490),b
	; @6D18 f761 sfta   b,1
	sfta   b,1
	; @6D19 f300 add    #12039,b
	add    #12039,b
	; @6D1B 8912 stlm   b,ar2
	stlm   b,ar2
	; @6D1C f030 and    #255,a
	and    #255,a
	; @6D1E 6882 andm   #-256,*ar2
	andm   #-256,*ar2
	; @6D20 1a82 or     *ar2,a
	or     *ar2,a
	; @6D21 8082 stl    a,*ar2
	stl    a,*ar2
	; @6D22 e800 ld     #0,a
	ld     #0,a
	; @6D23 7712 stm    #9340,ar2
	stm    #9340,ar2
	; @6D25 f074 call   0x5aa
	call   0x5aa
	; @6D27 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D2A f820 bc     0x6d2e,ntc
	bc     0x6d2e,ntc
	; @6D2C f074 call   0x7142
	call   0x7142
	; @6D2E ec03 rpt    #3
	rpt    #3
	; @6D2F 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6D30 7712 stm    #9352,ar2
	stm    #9352,ar2
	; @6D32 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D35 f820 bc     0x6d3b,ntc
	bc     0x6d3b,ntc
	; @6D37 e801 ld     #1,a
	ld     #1,a
	; @6D38 f074 call   0x7142
	call   0x7142
	; @6D3A e800 ld     #0,a
	ld     #0,a
	; @6D3B ec05 rpt    #5
	rpt    #5
	; @6D3C 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @6D3D 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D40 f830 bc     0x6d45,tc
	bc     0x6d45,tc
	; @6D42 76f8 st     #0,*(0x533)
	st     #0,*(0x533)
	; @6D45 f073 b      0x6ddb
	b      0x6ddb
	; @6D47 7713 stm    #16031,ar3
	stm    #16031,ar3
	; @6D49 61f8 bitf   *(0x2628),#64
	bitf   *(0x2628),#64
	; @6D4C f820 bc     0x6df6,ntc
	bc     0x6df6,ntc
	; @6D4E 7712 stm    #9354,ar2
	stm    #9354,ar2
	; @6D50 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D53 f820 bc     0x6d67,ntc
	bc     0x6d67,ntc
	; @6D55 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6D58 f830 bc     0x6d61,tc
	bc     0x6d61,tc
	; @6D5A 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6D5D f830 bc     0x6d65,tc
	bc     0x6d65,tc
	; @6D5F f073 b      0x6d67
	b      0x6d67
	; @6D61 f273 bd     0x6d67
	bd     0x6d67
	; @6D63 7712 stm    #13440,ar2
	stm    #13440,ar2
	; @6D65 7712 stm    #13448,ar2
	stm    #13448,ar2
	; @6D67 7714 stm    #9786,ar4
	stm    #9786,ar4
	; @6D69 6184 bitf   *ar4,#4096
	bitf   *ar4,#4096
	; @6D6B f820 bc     0x6d75,ntc
	bc     0x6d75,ntc
	; @6D6D 6184 bitf   *ar4,#1024
	bitf   *ar4,#1024
	; @6D6F f820 bc     0x6df6,ntc
	bc     0x6df6,ntc
	; @6D71 6082 cmpm   *ar2,#0
	cmpm   *ar2,#0
	; @6D73 f830 bc     0x6df6,tc
	bc     0x6df6,tc
	; @6D75 6884 andm   #-5121,*ar4
	andm   #-5121,*ar4
	; @6D77 11f8 ld     *(0x2611),b
	ld     *(0x2611),b
	; @6D79 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D7C 7714 stm    #9352,ar4
	stm    #9352,ar4
	; @6D7E f820 bc     0x6d8e,ntc
	bc     0x6d8e,ntc
	; @6D80 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6D83 f820 bc     0x6d87,ntc
	bc     0x6d87,ntc
	; @6D85 7714 stm    #13438,ar4
	stm    #13438,ar4
	; @6D87 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6D8A f820 bc     0x6d8e,ntc
	bc     0x6d8e,ntc
	; @6D8C 7714 stm    #13446,ar4
	stm    #13446,ar4
	; @6D8E f074 call   0x7067
	call   0x7067
	; @6D90 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6D93 f830 bc     0x6d9b,tc
	bc     0x6d9b,tc
	; @6D95 7712 stm    #12039,ar2
	stm    #12039,ar2
	; @6D97 80f8 stl    a,*(0x265d)
	stl    a,*(0x265d)
	; @6D99 f073 b      0x6db2
	b      0x6db2
	; @6D9B e907 ld     #7,b
	ld     #7,b
	; @6D9C 19f8 and    *(0x3490),b
	and    *(0x3490),b
	; @6D9E f310 sub    #1,b
	sub    #1,b
	; @6DA0 f495 nop
	nop
	; @6DA1 f495 nop
	nop
	.word 0xFF4B ; XC: gas encoder gap
	; @6DA3 80f8 stl    a,*(0x265d)
	stl    a,*(0x265d)
	.word 0xFF4D ; XC: gas encoder gap
	; @6DA6 80f8 stl    a,*(0x34bc)
	stl    a,*(0x34bc)
	.word 0xFF4E ; XC: gas encoder gap
	; @6DA9 80f8 stl    a,*(0x34bd)
	stl    a,*(0x34bd)
	; @6DAB e907 ld     #7,b
	ld     #7,b
	; @6DAC 19f8 and    *(0x3490),b
	and    *(0x3490),b
	; @6DAE f761 sfta   b,1
	sfta   b,1
	; @6DAF f300 add    #12039,b
	add    #12039,b
	; @6DB1 8912 stlm   b,ar2
	stlm   b,ar2
	; @6DB2 9438 ld     *ar5,8,a
	ld     *ar5,8,a
	; @6DB3 1a85 or     *ar5,a
	or     *ar5,a
	; @6DB4 8082 stl    a,*ar2
	stl    a,*ar2
	; @6DB5 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6DB8 f820 bc     0x6dd7,ntc
	bc     0x6dd7,ntc
	; @6DBA 10f8 ld     *(0x3490),a
	ld     *(0x3490),a
	; @6DBC f030 and    #7,a
	and    #7,a
	; @6DBE f010 sub    #1,a
	sub    #1,a
	; @6DC0 e900 ld     #0,b
	ld     #0,b
	; @6DC1 f845 bc     0x6dcb,aeq
	bc     0x6dcb,aeq
	; @6DC3 f846 bc     0x6dd1,agt
	bc     0x6dd1,agt
	; @6DC5 4ff8 dst    b,*(0x2488)
	dst    b,*(0x2488)
	; @6DC7 81f8 stl    b,*(0x248a)
	stl    b,*(0x248a)
	; @6DC9 f073 b      0x6ddb
	b      0x6ddb
	; @6DCB 4ff8 dst    b,*(0x347e)
	dst    b,*(0x347e)
	; @6DCD 81f8 stl    b,*(0x3480)
	stl    b,*(0x3480)
	; @6DCF f073 b      0x6ddb
	b      0x6ddb
	; @6DD1 4ff8 dst    b,*(0x3486)
	dst    b,*(0x3486)
	; @6DD3 81f8 stl    b,*(0x3488)
	stl    b,*(0x3488)
	; @6DD5 f073 b      0x6ddb
	b      0x6ddb
	; @6DD7 e800 ld     #0,a
	ld     #0,a
	; @6DD8 ec02 rpt    #2
	rpt    #2
	; @6DD9 7308 mvmd   al,0x2488
	mvmd   al,0x2488
	; @6DDB 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6DDE f820 bc     0x6df4,ntc
	bc     0x6df4,ntc
	; @6DE0 10f8 ld     *(0x34bf),a
	ld     *(0x34bf),a
	; @6DE2 f845 bc     0x6df4,aeq
	bc     0x6df4,aeq
	; @6DE4 f010 sub    #4,a
	sub    #4,a
	; @6DE6 f845 bc     0x6def,aeq
	bc     0x6def,aeq
	; @6DE8 e807 ld     #7,a
	ld     #7,a
	; @6DE9 18f8 and    *(0x3490),a
	and    *(0x3490),a
	; @6DEB f845 bc     0x6df6,aeq
	bc     0x6df6,aeq
	; @6DED f073 b      0x6df4
	b      0x6df4
	; @6DEF 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6DF2 f820 bc     0x6df6,ntc
	bc     0x6df6,ntc
	; @6DF4 f074 call   0x70a7
	call   0x70a7
	; @6DF6 f074 call   0x598
	call   0x598
	; @6DF8 61f8 bitf   *(0x51d),#256
	bitf   *(0x51d),#256
	; @6DFB f820 bc     0x6e96,ntc
	bc     0x6e96,ntc
	; @6DFD 61f8 bitf   *(0x3ec8),#64
	bitf   *(0x3ec8),#64
	; @6E00 f495 nop
	nop
	; @6E01 f495 nop
	nop
	; @6E02 f020 ld     #498,a
	ld     #498,a
	.word 0xFF30 ; XC: gas encoder gap
	; @6E05 f020 ld     #548,a
	ld     #548,a
	; @6E07 11f8 ld     *(0x3ec8),b
	ld     *(0x3ec8),b
	; @6E09 f330 and    #4096,b
	and    #4096,b
	; @6E0B f495 nop
	nop
	; @6E0C f495 nop
	nop
	.word 0xFF4E ; XC: gas encoder gap
	; @6E0E f020 ld     #473,a
	ld     #473,a
	; @6E10 61f8 bitf   *(0x263b),#128
	bitf   *(0x263b),#128
	; @6E13 f830 bc     0x6e2c,tc
	bc     0x6e2c,tc
	; @6E15 61f8 bitf   *(0x263b),#16
	bitf   *(0x263b),#16
	; @6E18 f820 bc     0x6e24,ntc
	bc     0x6e24,ntc
	; @6E1A e87c ld     #124,a
	ld     #124,a
	; @6E1B 61f8 bitf   *(0x3ec8),#64
	bitf   *(0x3ec8),#64
	; @6E1E f495 nop
	nop
	; @6E1F f495 nop
	nop
	.word 0xFD30 ; XC: gas encoder gap
	; @6E21 e8ae ld     #174,a
	ld     #174,a
	; @6E22 f073 b      0x6e2c
	b      0x6e2c
	; @6E24 61f8 bitf   *(0x263b),#32
	bitf   *(0x263b),#32
	; @6E27 f020 ld     #374,a
	ld     #374,a
	.word 0xFF20 ; XC: gas encoder gap
	; @6E2A f020 ld     #299,a
	ld     #299,a
	; @6E2C 08f8 sub    *(0x50b),a
	sub    *(0x50b),a
	; @6E2E f847 bc     0x6e96,aleq
	bc     0x6e96,aleq
	; @6E30 7713 stm    #1294,ar3
	stm    #1294,ar3
	; @6E32 1183 ld     *ar3,b
	ld     *ar3,b
	; @6E33 8083 stl    a,*ar3
	stl    a,*ar3
	; @6E34 f620 sub    b,a
	sub    b,a
	; @6E35 f010 sub    #1,a
	sub    #1,a
	; @6E37 881a stlm   a,brc
	stlm   a,brc
	; @6E38 f761 sfta   b,1
	sfta   b,1
	; @6E39 61f8 bitf   *(0x263b),#96
	bitf   *(0x263b),#96
	; @6E3C f020 ld     #3562,a
	ld     #3562,a
	; @6E3E f820 bc     0x6e4a,ntc
	bc     0x6e4a,ntc
	; @6E40 61f8 bitf   *(0x3ec8),#64
	bitf   *(0x3ec8),#64
	; @6E43 f495 nop
	nop
	; @6E44 f495 nop
	nop
	; @6E45 f020 ld     #3810,a
	ld     #3810,a
	.word 0xFF30 ; XC: gas encoder gap
	; @6E48 f020 ld     #3910,a
	ld     #3910,a
	; @6E4A f500 add    a,b
	add    a,b
	; @6E4B 8915 stlm   b,ar5
	stlm   b,ar5
	; @6E4C 7712 stm    #12034,ar2
	stm    #12034,ar2
	; @6E4E 61f8 bitf   *(0x3ec8),#16
	bitf   *(0x3ec8),#16
	; @6E51 7082 mvkd   0x58b,*ar2
	mvkd   0x58b,*ar2
	.word 0xFF20 ; XC: gas encoder gap
	; @6E54 7682 st     #5,*ar2
	st     #5,*ar2
	; @6E56 f272 rptbd  0x6e7b
	rptbd  0x6e7b
	; @6E58 7710 stm    #4,ar0
	stm    #4,ar0
	; @6E5A 7713 stm    #16031,ar3
	stm    #16031,ar3
	; @6E5C 7714 stm    #12035,ar4
	stm    #12035,ar4
	; @6E5E 1195 ld     *ar5+,b
	ld     *ar5+,b
	; @6E5F 1085 ld     *ar5,a
	ld     *ar5,a
	; @6E60 61f8 bitf   *(0x3ec8),#16
	bitf   *(0x3ec8),#16
	; @6E63 f495 nop
	nop
	; @6E64 f495 nop
	nop
	.word 0xFD30 ; XC: gas encoder gap
	; @6E66 f463 sfta   a,3
	sfta   a,3
	; @6E67 f274 calld  0x7067
	calld  0x7067
	; @6E69 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @6E6A 808c stl    a,*ar4-
	stl    a,*ar4-
	; @6E6B 7714 stm    #9,ar4
	stm    #9,ar4
	; @6E6D e753 mvmm   ar5,ar3
	mvmm   ar5,ar3
	; @6E6E 6d8b mar    *ar3-
	mar    *ar3-
	; @6E6F e556 mvdd   *ar3-,*ar4-
	mvdd   *ar3-,*ar4-
	; @6E70 a321 sub    *ar4,*ar3,b
	sub    *ar4,*ar3,b
	; @6E71 f84f bc     0x6e79,bleq
	bc     0x6e79,bleq
	; @6E73 5793 dld    *ar3+,b
	dld    *ar3+,b
	; @6E74 4f83 dst    b,*ar3
	dst    b,*ar3
	; @6E75 6dab mar    *ar3-0
	mar    *ar3-0
	; @6E76 a321 sub    *ar4,*ar3,b
	sub    *ar4,*ar3,b
	; @6E77 f84e bc     0x6e73,bgt
	bc     0x6e73,bgt
	; @6E79 6d93 mar    *ar3+
	mar    *ar3+
	; @6E7A 6d95 mar    *ar5+
	mar    *ar5+
	; @6E7B 4e83 dst    a,*ar3
	dst    a,*ar3
	; @6E7C 10f8 ld     *(0x50b),a
	ld     *(0x50b),a
	; @6E7E f844 bc     0x6e96,aneq
	bc     0x6e96,aneq
	; @6E80 68f8 andm   #-257,*(0x51d)
	andm   #-257,*(0x51d)
	; @6E83 61f8 bitf   *(0x263b),#96
	bitf   *(0x263b),#96
	; @6E86 f020 ld     #3561,a
	ld     #3561,a
	; @6E88 f820 bc     0x6e94,ntc
	bc     0x6e94,ntc
	; @6E8A 61f8 bitf   *(0x3ec8),#64
	bitf   *(0x3ec8),#64
	; @6E8D f495 nop
	nop
	; @6E8E f495 nop
	nop
	; @6E8F f020 ld     #3809,a
	ld     #3809,a
	.word 0xFF30 ; XC: gas encoder gap
	; @6E92 f020 ld     #3909,a
	ld     #3909,a
	; @6E94 f074 call   0x423b
	call   0x423b
	; @6E96 f074 call   0x598
	call   0x598
	; @6E98 61f8 bitf   *(0x2628),#3
	bitf   *(0x2628),#3
	; @6E9B f820 bc     0x6f52,ntc
	bc     0x6f52,ntc
	; @6E9D 7712 stm    #9786,ar2
	stm    #9786,ar2
	; @6E9F 6882 andm   #-1025,*ar2
	andm   #-1025,*ar2
	; @6EA1 f074 call   0x6f79
	call   0x6f79
	; @6EA3 7713 stm    #9311,ar3
	stm    #9311,ar3
	; @6EA5 808b stl    a,*ar3-
	stl    a,*ar3-
	; @6EA6 768b st     #9633,*ar3-
	st     #9633,*ar3-
	; @6EA8 6d8b mar    *ar3-
	mar    *ar3-
	; @6EA9 61f8 bitf   *(0x2628),#1
	bitf   *(0x2628),#1
	; @6EAC fa20 bcd    0x6f52,ntc
	bcd    0x6f52,ntc
	; @6EAE 10f8 ld     *(0x2476),a
	ld     *(0x2476),a
	; @6EB0 e900 ld     #0,b
	ld     #0,b
	; @6EB1 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6EB4 fa20 bcd    0x6ec6,ntc
	bcd    0x6ec6,ntc
	; @6EB6 7713 stm    #540,ar3
	stm    #540,ar3
	; @6EB8 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6EBB f820 bc     0x6ebf,ntc
	bc     0x6ebf,ntc
	; @6EBD 7713 stm    #13490,ar3
	stm    #13490,ar3
	; @6EBF 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6EC2 f820 bc     0x6ec6,ntc
	bc     0x6ec6,ntc
	; @6EC4 7713 stm    #13492,ar3
	stm    #13492,ar3
	; @6EC6 4f83 dst    b,*ar3
	dst    b,*ar3
	; @6EC7 81f8 stl    b,*(0x245c)
	stl    b,*(0x245c)
	; @6EC9 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6ECC f820 bc     0x6ed2,ntc
	bc     0x6ed2,ntc
	; @6ECE f074 call   0x712d
	call   0x712d
	; @6ED0 f820 bc     0x6ed5,ntc
	bc     0x6ed5,ntc
	; @6ED2 68f8 andm   #-33,*(0x2639)
	andm   #-33,*(0x2639)
	; @6ED5 f010 sub    #4,a
	sub    #4,a
	; @6ED7 7713 stm    #9821,ar3
	stm    #9821,ar3
	; @6ED9 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6EDC f820 bc     0x6eec,ntc
	bc     0x6eec,ntc
	; @6EDE 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6EE1 f820 bc     0x6ee5,ntc
	bc     0x6ee5,ntc
	; @6EE3 7713 stm    #13500,ar3
	stm    #13500,ar3
	; @6EE5 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6EE8 f820 bc     0x6eec,ntc
	bc     0x6eec,ntc
	; @6EEA 7713 stm    #13501,ar3
	stm    #13501,ar3
	.word 0xFF44 ; XC: gas encoder gap
	; @6EED 7713 stm    #9336,ar3
	stm    #9336,ar3
	; @6EEF 7712 stm    #9352,ar2
	stm    #9352,ar2
	; @6EF1 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6EF4 f820 bc     0x6ef9,ntc
	bc     0x6ef9,ntc
	; @6EF6 e801 ld     #1,a
	ld     #1,a
	; @6EF7 f074 call   0x7142
	call   0x7142
	; @6EF9 ec07 rpt    #7
	rpt    #7
	; @6EFA 8192 stl    b,*ar2+
	stl    b,*ar2+
	; @6EFB 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6EFE f830 bc     0x6f03,tc
	bc     0x6f03,tc
	; @6F00 76f8 st     #0,*(0x533)
	st     #0,*(0x533)
	; @6F03 61f8 bitf   *(0x3ec8),#32
	bitf   *(0x3ec8),#32
	; @6F06 f820 bc     0x6f21,ntc
	bc     0x6f21,ntc
	; @6F08 10f8 ld     *(0x2611),a
	ld     *(0x2611),a
	; @6F0A f110 sub    #124,a,b
	sub    #124,a,b
	; @6F0C fa4f bcd    0x6f16,bleq
	bcd    0x6f16,bleq
	; @6F0E 11f8 ld     *(0x3e9f),b
	ld     *(0x3e9f),b
	; @6F10 f010 sub    #975,a
	sub    #975,a
	; @6F12 f842 bc     0x6f16,ageq
	bc     0x6f16,ageq
	; @6F14 11f8 ld     *(0x3ee3),b
	ld     *(0x3ee3),b
	; @6F16 10f8 ld     *(0x3e97),a
	ld     *(0x3e97),a
	; @6F18 f620 sub    b,a
	sub    b,a
	; @6F19 9216 sub    *ar3,6,a
	sub    *ar3,6,a
	; @6F1A f274 calld  0x6fb1
	calld  0x6fb1
	; @6F1C 7712 stm    #9360,ar2
	stm    #9360,ar2
	; @6F1E 8082 stl    a,*ar2
	stl    a,*ar2
	; @6F1F f073 b      0x6f3e
	b      0x6f3e
	; @6F21 44f8 ld     *(0x3eb2),16,a
	ld     *(0x3eb2),16,a
	; @6F23 3cf8 add    *(0x3e94),16,a
	add    *(0x3e94),16,a
	; @6F25 61f8 bitf   *(0x51f),#128
	bitf   *(0x51f),#128
	; @6F28 f820 bc     0x6f39,ntc
	bc     0x6f39,ntc
	; @6F2A f120 ld     #975,b
	ld     #975,b
	; @6F2C 09f8 sub    *(0x260f),b
	sub    *(0x260f),b
	; @6F2E f84f bc     0x6f39,bleq
	bc     0x6f39,bleq
	; @6F30 e97c ld     #124,b
	ld     #124,b
	; @6F31 09f8 sub    *(0x260f),b
	sub    *(0x260f),b
	; @6F33 f84a bc     0x6f39,bgeq
	bc     0x6f39,bgeq
	; @6F35 44f8 ld     *(0x3ee0),16,a
	ld     *(0x3ee0),16,a
	; @6F37 3cf8 add    *(0x3edc),16,a
	add    *(0x3edc),16,a
	; @6F39 4083 sub    *ar3,16,a
	sub    *ar3,16,a
	; @6F3A f274 calld  0x6f88
	calld  0x6f88
	; @6F3C 7712 stm    #9360,ar2
	stm    #9360,ar2
	; @6F3E 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @6F41 f820 bc     0x6f51,ntc
	bc     0x6f51,ntc
	; @6F43 61f8 bitf   *(0x3490),#1
	bitf   *(0x3490),#1
	; @6F46 f820 bc     0x6f4a,ntc
	bc     0x6f4a,ntc
	; @6F48 7712 stm    #13457,ar2
	stm    #13457,ar2
	; @6F4A 61f8 bitf   *(0x3490),#2
	bitf   *(0x3490),#2
	; @6F4D f820 bc     0x6f51,ntc
	bc     0x6f51,ntc
	; @6F4F 7712 stm    #13458,ar2
	stm    #13458,ar2
	; @6F51 8082 stl    a,*ar2
	stl    a,*ar2
	; @6F52 61f8 bitf   *(0x2628),#512
	bitf   *(0x2628),#512
	; @6F55 f820 bc     0x6f63,ntc
	bc     0x6f63,ntc
	; @6F57 7713 stm    #9747,ar3
	stm    #9747,ar3
	; @6F59 10f8 ld     *(0x50b),a
	ld     *(0x50b),a
	; @6F5B f844 bc     0x6f61,aneq
	bc     0x6f61,aneq
	; @6F5D f074 call   0x6fda
	call   0x6fda
	; @6F5F f073 b      0x6f63
	b      0x6f63
	; @6F61 f074 call   0x6ffa
	call   0x6ffa
	; @6F63 61f8 bitf   *(0x2628),#256
	bitf   *(0x2628),#256
	; @6F66 f820 bc     0x6f74,ntc
	bc     0x6f74,ntc
	; @6F68 7713 stm    #9742,ar3
	stm    #9742,ar3
	; @6F6A 10f8 ld     *(0x50b),a
	ld     *(0x50b),a
	; @6F6C f844 bc     0x6f72,aneq
	bc     0x6f72,aneq
	; @6F6E f074 call   0x6fda
	call   0x6fda
	; @6F70 f073 b      0x6f74
	b      0x6f74
	; @6F72 f074 call   0x6ffa
	call   0x6ffa
	; @6F74 68f8 andm   #-2049,*(0x263a)
	andm   #-2049,*(0x263a)
	; @6F77 8a17 popm   ar7
	popm   ar7
	; @6F78 fc00 ret
	ret
