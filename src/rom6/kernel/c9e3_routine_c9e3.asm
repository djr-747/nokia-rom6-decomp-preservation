; ROM6 0xC9E3 ROUTINE_C9E3 -- 1058w, symbols.yaml data_word.
; Evidence: Entry F4BA 7712 10A0 E802 EC26; caller @C90E; first-RET FC00 @CE04; inner call E54B + RPT x3 + RPTBD x8; contains existing CA69 interior (address containment); interior exit-class 
; ORIGIN 0xC9E3
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @C9E3 f4ba rsbx   st0,ova
	rsbx   st0,ova
	; @C9E4 7712 stm    #4256,ar2
	stm    #4256,ar2
	; @C9E6 e802 ld     #2,a
	ld     #2,a
	; @C9E7 ec26 rpt    #38
	rpt    #38
	; @C9E8 3892 squra  *ar2+,a
	squra  *ar2+,a
	; @C9E9 3882 squra  *ar2,a
	squra  *ar2,a
	; @C9EA fa60 bcd    0xc9f4,anov
	bcd    0xc9f4,anov
	; @C9EC 7713 stm    #3393,ar3
	stm    #3393,ar3
	; @C9EE ed1f ld     #-1,asm
	ld     #-1,asm
	; @C9EF 448a ld     *ar2-,16,a
	ld     *ar2-,16,a
	; @C9F0 f273 bd     0xca0c
	bd     0xca0c
	; @C9F2 ec27 rpt    #39
	rpt    #39
	; @C9F3 c845 st     a,*ar3- || ld     *ar2-,a
	st     a,*ar3- || ld     *ar2-,a
	; @C9F4 f47f sfta   a,-1
	sfta   a,-1
	; @C9F5 f074 call   0xe54b
	call   0xe54b
	; @C9F7 7662 st     #-32768,0x62
	st     #-32768,0x62
	; @C9F9 f467 sfta   a,7
	sfta   a,7
	; @C9FA 770e stm    #32440,t
	stm    #32440,t
	; @C9FC f48c mpya   a
	mpya   a
	; @C9FD 82f8 sth    a,*(0xe)
	sth    a,*(0xe)
	; @C9FF 771a stm    #39,brc
	stm    #39,brc
	; @CA01 7712 stm    #4256,ar2
	stm    #4256,ar2
	; @CA03 7713 stm    #3354,ar3
	stm    #3354,ar3
	; @CA05 f272 rptbd  0xca0b
	rptbd  0xca0b
	; @CA07 ed00 ld     #0,asm
	ld     #0,asm
	; @CA08 2092 mpy    *ar2+,a
	mpy    *ar2+,a
	; @CA09 f469 sfta   a,9
	sfta   a,9
	; @CA0A 0262 adds   0x62,a
	adds   0x62,a
	; @CA0B cc89 st     a,*ar3+ || mpy    *ar2+,a
	st     a,*ar3+ || mpy    *ar2+,a
	; @CA0C 7712 stm    #3354,ar2
	stm    #3354,ar2
	; @CA0E e723 mvmm   ar2,ar3
	mvmm   ar2,ar3
	; @CA0F 7714 stm    #13631,ar4
	stm    #13631,ar4
	; @CA11 7710 stm    #-41,ar0
	stm    #-41,ar0
	; @CA13 771a stm    #38,brc
	stm    #38,brc
	; @CA15 e800 ld     #0,a
	ld     #0,a
	; @CA16 f272 rptbd  0xca1b
	rptbd  0xca1b
	; @CA18 ed00 ld     #0,asm
	ld     #0,asm
	; @CA19 b581 macr   *ar2+,*ar3,a,b
	macr   *ar2+,*ar3,a,b
	; @CA1A d29e st     b,*ar4+0% || mac    *ar3+,a
	st     b,*ar4+0% || mac    *ar3+,a
	; @CA1B b581 macr   *ar2+,*ar3,a,b
	macr   *ar2+,*ar3,a,b
	; @CA1C 8384 sth    b,*ar4
	sth    b,*ar4
	; @CA1D 6dec mar    *+ar4(0x617)
	mar    *+ar4(0x617)
	; @CA1F 7711 stm    #37,ar1
	stm    #37,ar1
	; @CA21 7716 stm    #3354,ar6
	stm    #3354,ar6
	; @CA23 7717 stm    #3355,ar7
	stm    #3355,ar7
	; @CA25 4811 ldm    ar1,a
	ldm    ar1,a
	; @CA26 881a stlm   a,brc
	stlm   a,brc
	; @CA27 e762 mvmm   ar6,ar2
	mvmm   ar6,ar2
	; @CA28 e773 mvmm   ar7,ar3
	mvmm   ar7,ar3
	; @CA29 e745 mvmm   ar4,ar5
	mvmm   ar4,ar5
	; @CA2A f272 rptbd  0xca2f
	rptbd  0xca2f
	; @CA2C e800 ld     #0,a
	ld     #0,a
	; @CA2D b581 macr   *ar2+,*ar3,a,b
	macr   *ar2+,*ar3,a,b
	; @CA2E d29f st     b,*ar5+0% || mac    *ar3+,a
	st     b,*ar5+0% || mac    *ar3+,a
	; @CA2F b581 macr   *ar2+,*ar3,a,b
	macr   *ar2+,*ar3,a,b
	; @CA30 e6ef st     b,*ar5+0% || ld     *ar4+0%,t
	st     b,*ar5+0% || ld     *ar4+0%,t
	; @CA31 6e89 banzd  0xca25,*ar1-
	banzd  0xca25,*ar1-
	; @CA33 6d94 mar    *ar4+
	mar    *ar4+
	; @CA34 6d97 mar    *ar7+
	mar    *ar7+
	; @CA35 3086 ld     *ar6,t
	ld     *ar6,t
	; @CA36 2387 mpyr   *ar7,b
	mpyr   *ar7,b
	; @CA37 8384 sth    b,*ar4
	sth    b,*ar4
	; @CA38 7717 stm    #12033,ar7
	stm    #12033,ar7
	; @CA3A 7713 stm    #3434,ar3
	stm    #3434,ar3
	; @CA3C 7710 stm    #40,ar0
	stm    #40,ar0
	; @CA3E 7711 stm    #37,ar1
	stm    #37,ar1
	; @CA40 7663 st     #37,0x63
	st     #37,0x63
	; @CA42 e774 mvmm   ar7,ar4
	mvmm   ar7,ar4
	; @CA43 e732 mvmm   ar3,ar2
	mvmm   ar3,ar2
	; @CA44 7163 mvdk   0x63,0x1a
	mvdk   0x63,0x1a
	; @CA46 e775 mvmm   ar7,ar5
	mvmm   ar7,ar5
	; @CA47 a568 mpy    *ar4-,*ar2+,b
	mpy    *ar4-,*ar2+,b
	; @CA48 a5e3 mpy    *ar4+0%,*ar5,b
	mpy    *ar4+0%,*ar5,b
	; @CA49 a418 mpy    *ar3,*ar2+,a
	mpy    *ar3,*ar2+,a
	; @CA4A 3197 mpya   *ar7+
	mpya   *ar7+
	; @CA4B f272 rptbd  0xca51
	rptbd  0xca51
	; @CA4D e61b st     b,*ar5+ || ld     *ar3,t
	st     b,*ar5+ || ld     *ar3,t
	; @CA4E 6ddf mar    *ar7+0%
	mar    *ar7+0%
	; @CA4F ce8e st     b,*ar4+0% || mpy    *ar2+,a
	st     b,*ar4+0% || mpy    *ar2+,a
	; @CA50 3185 mpya   *ar5
	mpya   *ar5
	; @CA51 e61b st     b,*ar5+ || ld     *ar3,t
	st     b,*ar5+ || ld     *ar3,t
	; @CA52 ca92 st     b,*ar4 || ld     *ar3+,a
	st     b,*ar4 || ld     *ar3+,a
	; @CA53 6e89 banzd  0xca42,*ar1-
	banzd  0xca42,*ar1-
	; @CA55 6b63 addm   #-1,0x63
	addm   #-1,0x63
	; @CA57 e774 mvmm   ar7,ar4
	mvmm   ar7,ar4
	; @CA58 e732 mvmm   ar3,ar2
	mvmm   ar3,ar2
	; @CA59 e775 mvmm   ar7,ar5
	mvmm   ar7,ar5
	; @CA5A a568 mpy    *ar4-,*ar2+,b
	mpy    *ar4-,*ar2+,b
	; @CA5B 6db4 mar    *ar4+0
	mar    *ar4+0
	; @CA5C a418 mpy    *ar3,*ar2+,a
	mpy    *ar3,*ar2+,a
	; @CA5D 3185 mpya   *ar5
	mpya   *ar5
	; @CA5E 8385 sth    b,*ar5
	sth    b,*ar5
	; @CA5F 8384 sth    b,*ar4
	sth    b,*ar4
	; @CA60 7712 stm    #12032,ar2
	stm    #12032,ar2
	; @CA62 7713 stm    #3354,ar3
	stm    #3354,ar3
	; @CA64 7710 stm    #41,ar0
	stm    #41,ar0
	; @CA66 fe00 retd
	retd
	; @CA67 ec27 rpt    #39
	rpt    #39
	; @CA68 e5c9 mvdd   *ar2+0%,*ar3+
	mvdd   *ar2+0%,*ar3+
	; @CA69 7666 st     #3354,0x66
	st     #3354,0x66
	; @CA6B 7665 st     #12032,0x65
	st     #12032,0x65
	; @CA6D 7667 st     #3314,0x67
	st     #3314,0x67
	; @CA6F 7712 stm    #120,ar2
	stm    #120,ar2
	; @CA71 ec07 rpt    #7
	rpt    #7
	; @CA72 7092 mvkd   0xb628,*ar2+
	mvkd   0xb628,*ar2+
	; @CA74 7674 st     #1,0x74
	st     #1,0x74
	; @CA76 7675 st     #-1,0x75
	st     #-1,0x75
	; @CA78 10f8 ld     *(0x1046),a
	ld     *(0x1046),a
	; @CA7A 8812 stlm   a,ar2
	stlm   a,ar2
	; @CA7B e805 ld     #5,a
	ld     #5,a
	; @CA7C 8077 stl    a,0x77
	stl    a,0x77
	; @CA7D 8810 stlm   a,ar0
	stlm   a,ar0
	; @CA7E 6dea mar    *+ar2(0x1058)
	mar    *+ar2(0x1058)
	; @CA80 7182 mvdk   *ar2,0x68
	mvdk   *ar2,0x68
	; @CA82 7711 stm    #3,ar1
	stm    #3,ar1
	; @CA84 4a11 pshm   ar1
	pshm   ar1
	; @CA85 10f8 ld     *(0x1047),a
	ld     *(0x1047),a
	; @CA87 8812 stlm   a,ar2
	stlm   a,ar2
	; @CA88 1068 ld     0x68,a
	ld     0x68,a
	; @CA89 8815 stlm   a,ar5
	stlm   a,ar5
	; @CA8A 0067 add    0x67,a
	add    0x67,a
	; @CA8B 8813 stlm   a,ar3
	stlm   a,ar3
	; @CA8C 6dea mar    *+ar2(0x1058)
	mar    *+ar2(0x1058)
	; @CA8E 1082 ld     *ar2,a
	ld     *ar2,a
	; @CA8F 8069 stl    a,0x69
	stl    a,0x69
	; @CA90 8812 stlm   a,ar2
	stlm   a,ar2
	; @CA91 0067 add    0x67,a
	add    0x67,a
	; @CA92 8814 stlm   a,ar4
	stlm   a,ar4
	; @CA93 6ded mar    *+ar5(0xd1a)
	mar    *+ar5(0xd1a)
	; @CA95 3078 ld     0x78,t
	ld     0x78,t
	; @CA96 a012 add    *ar3,*ar4,a
	add    *ar3,*ar4,a
	; @CA97 8264 sth    a,0x64
	sth    a,0x64
	; @CA98 2068 mpy    0x68,a
	mpy    0x68,a
	; @CA99 0069 add    0x69,a
	add    0x69,a
	; @CA9A 0065 add    0x65,a
	add    0x65,a
	; @CA9B 8813 stlm   a,ar3
	stlm   a,ar3
	; @CA9C 6dea mar    *+ar2(0xd1a)
	mar    *+ar2(0xd1a)
	; @CA9E 943c ld     *ar5,12,a
	ld     *ar5,12,a
	; @CA9F 900c add    *ar2,12,a
	add    *ar2,12,a
	; @CAA0 901d add    *ar3,13,a
	add    *ar3,13,a
	; @CAA1 4e62 dst    a,0x62
	dst    a,0x62
	; @CAA2 7711 stm    #4169,ar1
	stm    #4169,ar1
	; @CAA4 1066 ld     0x66,a
	ld     0x66,a
	; @CAA5 0081 add    *ar1,a
	add    *ar1,a
	; @CAA6 8812 stlm   a,ar2
	stlm   a,ar2
	; @CAA7 1065 ld     0x65,a
	ld     0x65,a
	; @CAA8 0089 add    *ar1-,a
	add    *ar1-,a
	; @CAA9 2168 mpy    0x68,b
	mpy    0x68,b
	; @CAAA f500 add    a,b
	add    a,b
	; @CAAB 8913 stlm   b,ar3
	stlm   b,ar3
	; @CAAC 2869 mac    0x69,a
	mac    0x69,a
	; @CAAD 8814 stlm   a,ar4
	stlm   a,ar4
	; @CAAE 307e ld     0x7e,t
	ld     0x7e,t
	; @CAAF 771a stm    #7,brc
	stm    #7,brc
	; @CAB1 21db mpy    *ar3+0%,b
	mpy    *ar3+0%,b
	; @CAB2 f272 rptbd  0xcab8
	rptbd  0xcab8
	; @CAB4 7715 stm    #4176,ar5
	stm    #4176,ar5
	; @CAB6 91cd add    *ar2+0%,13,b
	add    *ar2+0%,13,b
	; @CAB7 2bdc macr   *ar4+0%,b
	macr   *ar4+0%,b
	; @CAB8 cfdb st     b,*ar5+ || mpy    *ar3+0%,b
	st     b,*ar5+ || mpy    *ar3+0%,b
	; @CAB9 1067 ld     0x67,a
	ld     0x67,a
	; @CABA 0081 add    *ar1,a
	add    *ar1,a
	; @CABB 8812 stlm   a,ar2
	stlm   a,ar2
	; @CABC 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CABE 4464 ld     0x64,16,a
	ld     0x64,16,a
	; @CABF 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CAC0 ec06 rpt    #6
	rpt    #6
	; @CAC1 c3c9 st     b,*ar3+ || add    *ar2+0%,b
	st     b,*ar3+ || add    *ar2+0%,b
	; @CAC2 8383 sth    b,*ar3
	sth    b,*ar3
	; @CAC3 3078 ld     0x78,t
	ld     0x78,t
	; @CAC4 1066 ld     0x66,a
	ld     0x66,a
	; @CAC5 0081 add    *ar1,a
	add    *ar1,a
	; @CAC6 8812 stlm   a,ar2
	stlm   a,ar2
	; @CAC7 1065 ld     0x65,a
	ld     0x65,a
	; @CAC8 2868 mac    0x68,a
	mac    0x68,a
	; @CAC9 0081 add    *ar1,a
	add    *ar1,a
	; @CACA 8813 stlm   a,ar3
	stlm   a,ar3
	; @CACB 1065 ld     0x65,a
	ld     0x65,a
	; @CACC 2869 mac    0x69,a
	mac    0x69,a
	; @CACD 0091 add    *ar1+,a
	add    *ar1+,a
	; @CACE 8814 stlm   a,ar4
	stlm   a,ar4
	; @CACF 771a stm    #7,brc
	stm    #7,brc
	; @CAD1 307b ld     0x7b,t
	ld     0x7b,t
	; @CAD2 5662 dld    0x62,a
	dld    0x62,a
	; @CAD3 f272 rptbd  0xcadb
	rptbd  0xcadb
	; @CAD5 7716 stm    #4394,ar6
	stm    #4394,ar6
	; @CAD7 6fda add    *ar2+0%,12,a,b
	add    *ar2+0%,12,a,b
	; @CAD9 29db mac    *ar3+0%,b
	mac    *ar3+0%,b
	; @CADA 29dc mac    *ar4+0%,b
	mac    *ar4+0%,b
	; @CADB 4f96 dst    b,*ar6+
	dst    b,*ar6+
	; @CADC 1067 ld     0x67,a
	ld     0x67,a
	; @CADD 0081 add    *ar1,a
	add    *ar1,a
	; @CADE 8812 stlm   a,ar2
	stlm   a,ar2
	; @CADF 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CAE1 771a stm    #7,brc
	stm    #7,brc
	; @CAE3 e726 mvmm   ar2,ar6
	mvmm   ar2,ar6
	; @CAE4 f272 rptbd  0xcaed
	rptbd  0xcaed
	; @CAE6 7714 stm    #4192,ar4
	stm    #4192,ar4
	; @CAE8 4493 ld     *ar3+,16,a
	ld     *ar3+,16,a
	; @CAE9 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CAEA ec06 rpt    #6
	rpt    #6
	; @CAEB c3ca st     b,*ar4+ || add    *ar2+0%,b
	st     b,*ar4+ || add    *ar2+0%,b
	; @CAEC 8394 sth    b,*ar4+
	sth    b,*ar4+
	; @CAED e762 mvmm   ar6,ar2
	mvmm   ar6,ar2
	; @CAEE 1089 ld     *ar1-,a
	ld     *ar1-,a
	; @CAEF 3081 ld     *ar1,t
	ld     *ar1,t
	; @CAF0 2878 mac    0x78,a
	mac    0x78,a
	; @CAF1 0065 add    0x65,a
	add    0x65,a
	; @CAF2 8812 stlm   a,ar2
	stlm   a,ar2
	; @CAF3 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CAF5 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CAF7 e737 mvmm   ar3,ar7
	mvmm   ar3,ar7
	; @CAF8 7715 stm    #122,ar5
	stm    #122,ar5
	; @CAFA 771a stm    #7,brc
	stm    #7,brc
	; @CAFC f272 rptbd  0xcb1b
	rptbd  0xcb1b
	; @CAFE 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CB00 5791 dld    *ar1+,b
	dld    *ar1+,b
	; @CB01 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB02 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB03 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB04 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB05 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB06 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB07 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB08 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB09 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB0A b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB0B b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB0C 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB0D b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB0E b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB0F 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB10 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB11 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB12 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB13 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB14 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB15 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB16 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CB17 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CB18 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CB19 6dea mar    *+ar2(0xa0)
	mar    *+ar2(0xa0)
	; @CB1B e773 mvmm   ar7,ar3
	mvmm   ar7,ar3
	; @CB1C 771a stm    #63,brc
	stm    #63,brc
	; @CB1E 7712 stm    #4192,ar2
	stm    #4192,ar2
	; @CB20 7713 stm    #114,ar3
	stm    #114,ar3
	; @CB22 7693 st     #1,*ar3+
	st     #1,*ar3+
	; @CB24 768b st     #-1,*ar3-
	st     #-1,*ar3-
	; @CB26 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CB28 7715 stm    #118,ar5
	stm    #118,ar5
	; @CB2A 6ff8 ld     *(0x1048),3,a
	ld     *(0x1048),3,a
	; @CB2D 00f8 add    *(0x1049),a
	add    *(0x1049),a
	; @CB2F 8085 stl    a,*ar5
	stl    a,*ar5
	; @CB30 f272 rptbd  0xcb39
	rptbd  0xcb39
	; @CB32 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CB33 3193 mpya   *ar3+
	mpya   *ar3+
	; @CB34 bba5 mas    *ar4+,*ar3-,b
	mas    *ar4+,*ar3-,b
	; @CB35 9d3e srccd  *ar5,bgt
	srccd  *ar5,bgt
	; @CB36 9c9e strcd  *ar3+,bgt
	strcd  *ar3+,bgt
	; @CB37 9e5e saccd  a,*ar3-,bgt
	saccd  a,*ar3-,bgt
	; @CB38 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CB39 3193 mpya   *ar3+
	mpya   *ar3+
	; @CB3A 6f79 ld     0x79,13,a
	ld     0x79,13,a
	; @CB3C 923d sub    *ar5,13,a
	sub    *ar5,13,a
	; @CB3D 6f13 sth    a,3,0x13
	sth    a,3,0x13
	; @CB3F 3177 mpya   0x77
	mpya   0x77
	; @CB40 4009 sub    0x09,16,a
	sub    0x09,16,a
	; @CB41 6ff8 add    *(0x1048),1,b
	add    *(0x1048),1,b
	; @CB44 6f6a sth    b,15,0x6a
	sth    b,15,0x6a
	; @CB46 f463 sfta   a,3
	sfta   a,3
	; @CB47 3177 mpya   0x77
	mpya   0x77
	; @CB48 6ff8 add    *(0x1049),1,b
	add    *(0x1049),1,b
	; @CB4B 6f6b sth    b,15,0x6b
	sth    b,15,0x6b
	; @CB4D e734 mvmm   ar3,ar4
	mvmm   ar3,ar4
	; @CB4E 6deb mar    *+ar3(0x10fa)
	mar    *+ar3(0x10fa)
	; @CB50 6dec mar    *+ar4(0x1060)
	mar    *+ar4(0x1060)
	; @CB52 7711 stm    #4171,ar1
	stm    #4171,ar1
	; @CB54 1084 ld     *ar4,a
	ld     *ar4,a
	; @CB55 8064 stl    a,0x64
	stl    a,0x64
	; @CB56 941f ld     *ar3,15,a
	ld     *ar3,15,a
	; @CB57 4e62 dst    a,0x62
	dst    a,0x62
	; @CB58 7712 stm    #120,ar2
	stm    #120,ar2
	; @CB5A 7713 stm    #104,ar3
	stm    #104,ar3
	; @CB5C 1081 ld     *ar1,a
	ld     *ar1,a
	; @CB5D 0065 add    0x65,a
	add    0x65,a
	; @CB5E b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB5F 8914 stlm   b,ar4
	stlm   b,ar4
	; @CB60 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB61 8915 stlm   b,ar5
	stlm   b,ar5
	; @CB62 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB63 8916 stlm   b,ar6
	stlm   b,ar6
	; @CB64 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB65 8917 stlm   b,ar7
	stlm   b,ar7
	; @CB66 1089 ld     *ar1-,a
	ld     *ar1-,a
	; @CB67 8812 stlm   a,ar2
	stlm   a,ar2
	; @CB68 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CB6A 307e ld     0x7e,t
	ld     0x7e,t
	; @CB6B 771a stm    #7,brc
	stm    #7,brc
	; @CB6D 20dc mpy    *ar4+0%,a
	mpy    *ar4+0%,a
	; @CB6E f272 rptbd  0xcb76
	rptbd  0xcb76
	; @CB70 6dea mar    *+ar2(0xd1a)
	mar    *+ar2(0xd1a)
	; @CB72 90cd add    *ar2+0%,13,a
	add    *ar2+0%,13,a
	; @CB73 28df mac    *ar7+0%,a
	mac    *ar7+0%,a
	; @CB74 28de mac    *ar6+0%,a
	mac    *ar6+0%,a
	; @CB75 2add macr   *ar5+0%,a
	macr   *ar5+0%,a
	; @CB76 cce9 st     a,*ar3+ || mpy    *ar4+0%,a
	st     a,*ar3+ || mpy    *ar4+0%,a
	; @CB77 1067 ld     0x67,a
	ld     0x67,a
	; @CB78 0081 add    *ar1,a
	add    *ar1,a
	; @CB79 8812 stlm   a,ar2
	stlm   a,ar2
	; @CB7A 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CB7C 4464 ld     0x64,16,a
	ld     0x64,16,a
	; @CB7D 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CB7E ec06 rpt    #6
	rpt    #6
	; @CB7F c3c9 st     b,*ar3+ || add    *ar2+0%,b
	st     b,*ar3+ || add    *ar2+0%,b
	; @CB80 8383 sth    b,*ar3
	sth    b,*ar3
	; @CB81 3078 ld     0x78,t
	ld     0x78,t
	; @CB82 1066 ld     0x66,a
	ld     0x66,a
	; @CB83 0081 add    *ar1,a
	add    *ar1,a
	; @CB84 8814 stlm   a,ar4
	stlm   a,ar4
	; @CB85 1065 ld     0x65,a
	ld     0x65,a
	; @CB86 0091 add    *ar1+,a
	add    *ar1+,a
	; @CB87 7713 stm    #104,ar3
	stm    #104,ar3
	; @CB89 7712 stm    #120,ar2
	stm    #120,ar2
	; @CB8B b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB8C 8915 stlm   b,ar5
	stlm   b,ar5
	; @CB8D b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB8E 8916 stlm   b,ar6
	stlm   b,ar6
	; @CB8F b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CB90 8917 stlm   b,ar7
	stlm   b,ar7
	; @CB91 2883 mac    *ar3,a
	mac    *ar3,a
	; @CB92 8812 stlm   a,ar2
	stlm   a,ar2
	; @CB93 771a stm    #7,brc
	stm    #7,brc
	; @CB95 307d ld     0x7d,t
	ld     0x7d,t
	; @CB96 5662 dld    0x62,a
	dld    0x62,a
	; @CB97 f272 rptbd  0xcba1
	rptbd  0xcba1
	; @CB99 7713 stm    #4394,ar3
	stm    #4394,ar3
	; @CB9B 6fdc add    *ar4+0%,11,a,b
	add    *ar4+0%,11,a,b
	; @CB9D 29da mac    *ar2+0%,b
	mac    *ar2+0%,b
	; @CB9E 29df mac    *ar7+0%,b
	mac    *ar7+0%,b
	; @CB9F 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CBA0 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CBA1 4f93 dst    b,*ar3+
	dst    b,*ar3+
	; @CBA2 1067 ld     0x67,a
	ld     0x67,a
	; @CBA3 0081 add    *ar1,a
	add    *ar1,a
	; @CBA4 8812 stlm   a,ar2
	stlm   a,ar2
	; @CBA5 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CBA7 771a stm    #7,brc
	stm    #7,brc
	; @CBA9 e726 mvmm   ar2,ar6
	mvmm   ar2,ar6
	; @CBAA f272 rptbd  0xcbb3
	rptbd  0xcbb3
	; @CBAC 7714 stm    #4192,ar4
	stm    #4192,ar4
	; @CBAE 4493 ld     *ar3+,16,a
	ld     *ar3+,16,a
	; @CBAF 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CBB0 ec06 rpt    #6
	rpt    #6
	; @CBB1 c3ca st     b,*ar4+ || add    *ar2+0%,b
	st     b,*ar4+ || add    *ar2+0%,b
	; @CBB2 8394 sth    b,*ar4+
	sth    b,*ar4+
	; @CBB3 e762 mvmm   ar6,ar2
	mvmm   ar6,ar2
	; @CBB4 1089 ld     *ar1-,a
	ld     *ar1-,a
	; @CBB5 3081 ld     *ar1,t
	ld     *ar1,t
	; @CBB6 2878 mac    0x78,a
	mac    0x78,a
	; @CBB7 0065 add    0x65,a
	add    0x65,a
	; @CBB8 8812 stlm   a,ar2
	stlm   a,ar2
	; @CBB9 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CBBB 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CBBD e737 mvmm   ar3,ar7
	mvmm   ar3,ar7
	; @CBBE 7715 stm    #126,ar5
	stm    #126,ar5
	; @CBC0 771a stm    #7,brc
	stm    #7,brc
	; @CBC2 f272 rptbd  0xcbe1
	rptbd  0xcbe1
	; @CBC4 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CBC6 5791 dld    *ar1+,b
	dld    *ar1+,b
	; @CBC7 b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBC8 b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBC9 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBCA b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBCB b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBCC 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBCD b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBCE b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBCF 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBD0 b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBD1 b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBD2 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBD3 b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBD4 b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBD5 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBD6 b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBD7 b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBD8 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBD9 b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBDA b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBDB 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBDC b297 mac    *ar3+,*ar5-,b,a
	mac    *ar3+,*ar5-,b,a
	; @CBDD b4cb macr   *ar2+0%,*ar5+,a
	macr   *ar2+0%,*ar5+,a
	; @CBDE 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CBDF 6dea mar    *+ar2(0xa0)
	mar    *+ar2(0xa0)
	; @CBE1 e773 mvmm   ar7,ar3
	mvmm   ar7,ar3
	; @CBE2 771a stm    #63,brc
	stm    #63,brc
	; @CBE4 7712 stm    #4192,ar2
	stm    #4192,ar2
	; @CBE6 7713 stm    #114,ar3
	stm    #114,ar3
	; @CBE8 7693 st     #1,*ar3+
	st     #1,*ar3+
	; @CBEA 768b st     #-1,*ar3-
	st     #-1,*ar3-
	; @CBEC 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CBEE 7715 stm    #118,ar5
	stm    #118,ar5
	; @CBF0 6ff8 ld     *(0x104a),3,a
	ld     *(0x104a),3,a
	; @CBF3 00f8 add    *(0x104b),a
	add    *(0x104b),a
	; @CBF5 8085 stl    a,*ar5
	stl    a,*ar5
	; @CBF6 f272 rptbd  0xcbff
	rptbd  0xcbff
	; @CBF8 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CBF9 3193 mpya   *ar3+
	mpya   *ar3+
	; @CBFA bba5 mas    *ar4+,*ar3-,b
	mas    *ar4+,*ar3-,b
	; @CBFB 9d3e srccd  *ar5,bgt
	srccd  *ar5,bgt
	; @CBFC 9c9e strcd  *ar3+,bgt
	strcd  *ar3+,bgt
	; @CBFD 9e5e saccd  a,*ar3-,bgt
	saccd  a,*ar3-,bgt
	; @CBFE 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CBFF 3193 mpya   *ar3+
	mpya   *ar3+
	; @CC00 6f79 ld     0x79,13,a
	ld     0x79,13,a
	; @CC02 923d sub    *ar5,13,a
	sub    *ar5,13,a
	; @CC03 6f13 sth    a,3,0x13
	sth    a,3,0x13
	; @CC05 3177 mpya   0x77
	mpya   0x77
	; @CC06 4009 sub    0x09,16,a
	sub    0x09,16,a
	; @CC07 6ff8 add    *(0x104a),1,b
	add    *(0x104a),1,b
	; @CC0A 6f6c sth    b,15,0x6c
	sth    b,15,0x6c
	; @CC0C f463 sfta   a,3
	sfta   a,3
	; @CC0D 3177 mpya   0x77
	mpya   0x77
	; @CC0E 6ff8 add    *(0x104b),1,b
	add    *(0x104b),1,b
	; @CC11 6f6d sth    b,15,0x6d
	sth    b,15,0x6d
	; @CC13 e734 mvmm   ar3,ar4
	mvmm   ar3,ar4
	; @CC14 6deb mar    *+ar3(0x10fa)
	mar    *+ar3(0x10fa)
	; @CC16 6dec mar    *+ar4(0x1060)
	mar    *+ar4(0x1060)
	; @CC18 7711 stm    #4173,ar1
	stm    #4173,ar1
	; @CC1A 1084 ld     *ar4,a
	ld     *ar4,a
	; @CC1B 8064 stl    a,0x64
	stl    a,0x64
	; @CC1C 941f ld     *ar3,15,a
	ld     *ar3,15,a
	; @CC1D 4e62 dst    a,0x62
	dst    a,0x62
	; @CC1E 7712 stm    #120,ar2
	stm    #120,ar2
	; @CC20 7713 stm    #104,ar3
	stm    #104,ar3
	; @CC22 1081 ld     *ar1,a
	ld     *ar1,a
	; @CC23 0065 add    0x65,a
	add    0x65,a
	; @CC24 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC25 8914 stlm   b,ar4
	stlm   b,ar4
	; @CC26 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC27 8915 stlm   b,ar5
	stlm   b,ar5
	; @CC28 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC29 8916 stlm   b,ar6
	stlm   b,ar6
	; @CC2A 771a stm    #7,brc
	stm    #7,brc
	; @CC2C 307b ld     0x7b,t
	ld     0x7b,t
	; @CC2D f272 rptbd  0xcc34
	rptbd  0xcc34
	; @CC2F 7717 stm    #4394,ar7
	stm    #4394,ar7
	; @CC31 21dc mpy    *ar4+0%,b
	mpy    *ar4+0%,b
	; @CC32 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CC33 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CC34 4f97 dst    b,*ar7+
	dst    b,*ar7+
	; @CC35 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC36 8914 stlm   b,ar4
	stlm   b,ar4
	; @CC37 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC38 8915 stlm   b,ar5
	stlm   b,ar5
	; @CC39 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC3A 8916 stlm   b,ar6
	stlm   b,ar6
	; @CC3B 1089 ld     *ar1-,a
	ld     *ar1-,a
	; @CC3C 8812 stlm   a,ar2
	stlm   a,ar2
	; @CC3D 7717 stm    #4394,ar7
	stm    #4394,ar7
	; @CC3F 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CC41 771a stm    #7,brc
	stm    #7,brc
	; @CC43 307b ld     0x7b,t
	ld     0x7b,t
	; @CC44 20dc mpy    *ar4+0%,a
	mpy    *ar4+0%,a
	; @CC45 f272 rptbd  0xcc4d
	rptbd  0xcc4d
	; @CC47 6dea mar    *+ar2(0xd1a)
	mar    *+ar2(0xd1a)
	; @CC49 5097 dadd   *ar7+,a
	dadd   *ar7+,a
	; @CC4A 90cc add    *ar2+0%,12,a
	add    *ar2+0%,12,a
	; @CC4B 28dd mac    *ar5+0%,a
	mac    *ar5+0%,a
	; @CC4C 2ade macr   *ar6+0%,a
	macr   *ar6+0%,a
	; @CC4D cce9 st     a,*ar3+ || mpy    *ar4+0%,a
	st     a,*ar3+ || mpy    *ar4+0%,a
	; @CC4E 1067 ld     0x67,a
	ld     0x67,a
	; @CC4F 0081 add    *ar1,a
	add    *ar1,a
	; @CC50 8812 stlm   a,ar2
	stlm   a,ar2
	; @CC51 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CC53 4464 ld     0x64,16,a
	ld     0x64,16,a
	; @CC54 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CC55 ec06 rpt    #6
	rpt    #6
	; @CC56 c3c9 st     b,*ar3+ || add    *ar2+0%,b
	st     b,*ar3+ || add    *ar2+0%,b
	; @CC57 8383 sth    b,*ar3
	sth    b,*ar3
	; @CC58 7712 stm    #120,ar2
	stm    #120,ar2
	; @CC5A 7713 stm    #104,ar3
	stm    #104,ar3
	; @CC5C 1065 ld     0x65,a
	ld     0x65,a
	; @CC5D 0081 add    *ar1,a
	add    *ar1,a
	; @CC5E b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC5F 8914 stlm   b,ar4
	stlm   b,ar4
	; @CC60 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC61 8915 stlm   b,ar5
	stlm   b,ar5
	; @CC62 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC63 8916 stlm   b,ar6
	stlm   b,ar6
	; @CC64 771a stm    #7,brc
	stm    #7,brc
	; @CC66 307f ld     0x7f,t
	ld     0x7f,t
	; @CC67 f272 rptbd  0xcc6e
	rptbd  0xcc6e
	; @CC69 7717 stm    #4394,ar7
	stm    #4394,ar7
	; @CC6B 21dc mpy    *ar4+0%,b
	mpy    *ar4+0%,b
	; @CC6C 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CC6D 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CC6E 4f97 dst    b,*ar7+
	dst    b,*ar7+
	; @CC6F b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC70 8914 stlm   b,ar4
	stlm   b,ar4
	; @CC71 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC72 8915 stlm   b,ar5
	stlm   b,ar5
	; @CC73 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CC74 8916 stlm   b,ar6
	stlm   b,ar6
	; @CC75 1091 ld     *ar1+,a
	ld     *ar1+,a
	; @CC76 0066 add    0x66,a
	add    0x66,a
	; @CC77 8812 stlm   a,ar2
	stlm   a,ar2
	; @CC78 771a stm    #7,brc
	stm    #7,brc
	; @CC7A 307f ld     0x7f,t
	ld     0x7f,t
	; @CC7B 5662 dld    0x62,a
	dld    0x62,a
	; @CC7C f272 rptbd  0xcc86
	rptbd  0xcc86
	; @CC7E 7713 stm    #4394,ar3
	stm    #4394,ar3
	; @CC80 6fda add    *ar2+0%,10,a,b
	add    *ar2+0%,10,a,b
	; @CC82 5383 dadd   *ar3,b
	dadd   *ar3,b
	; @CC83 29dc mac    *ar4+0%,b
	mac    *ar4+0%,b
	; @CC84 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CC85 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CC86 4f93 dst    b,*ar3+
	dst    b,*ar3+
	; @CC87 1067 ld     0x67,a
	ld     0x67,a
	; @CC88 0081 add    *ar1,a
	add    *ar1,a
	; @CC89 8812 stlm   a,ar2
	stlm   a,ar2
	; @CC8A 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CC8C 771a stm    #7,brc
	stm    #7,brc
	; @CC8E e726 mvmm   ar2,ar6
	mvmm   ar2,ar6
	; @CC8F f272 rptbd  0xcc98
	rptbd  0xcc98
	; @CC91 7714 stm    #4192,ar4
	stm    #4192,ar4
	; @CC93 4493 ld     *ar3+,16,a
	ld     *ar3+,16,a
	; @CC94 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CC95 ec06 rpt    #6
	rpt    #6
	; @CC96 c3ca st     b,*ar4+ || add    *ar2+0%,b
	st     b,*ar4+ || add    *ar2+0%,b
	; @CC97 8394 sth    b,*ar4+
	sth    b,*ar4+
	; @CC98 e762 mvmm   ar6,ar2
	mvmm   ar6,ar2
	; @CC99 1089 ld     *ar1-,a
	ld     *ar1-,a
	; @CC9A 3081 ld     *ar1,t
	ld     *ar1,t
	; @CC9B 2878 mac    0x78,a
	mac    0x78,a
	; @CC9C 0065 add    0x65,a
	add    0x65,a
	; @CC9D 8812 stlm   a,ar2
	stlm   a,ar2
	; @CC9E 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CCA0 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CCA2 e737 mvmm   ar3,ar7
	mvmm   ar3,ar7
	; @CCA3 7715 stm    #126,ar5
	stm    #126,ar5
	; @CCA5 771a stm    #7,brc
	stm    #7,brc
	; @CCA7 f272 rptbd  0xccc6
	rptbd  0xccc6
	; @CCA9 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CCAB 5791 dld    *ar1+,b
	dld    *ar1+,b
	; @CCAC b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCAD b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCAE 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCAF b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCB0 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCB1 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCB2 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCB3 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCB4 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCB5 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCB6 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCB7 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCB8 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCB9 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCBA 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCBB b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCBC b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCBD 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCBE b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCBF b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCC0 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCC1 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CCC2 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CCC3 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CCC4 6dea mar    *+ar2(0xa0)
	mar    *+ar2(0xa0)
	; @CCC6 e773 mvmm   ar7,ar3
	mvmm   ar7,ar3
	; @CCC7 771a stm    #63,brc
	stm    #63,brc
	; @CCC9 7712 stm    #4192,ar2
	stm    #4192,ar2
	; @CCCB 7713 stm    #114,ar3
	stm    #114,ar3
	; @CCCD 7693 st     #1,*ar3+
	st     #1,*ar3+
	; @CCCF 768b st     #-1,*ar3-
	st     #-1,*ar3-
	; @CCD1 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CCD3 7715 stm    #118,ar5
	stm    #118,ar5
	; @CCD5 6ff8 ld     *(0x104c),3,a
	ld     *(0x104c),3,a
	; @CCD8 00f8 add    *(0x104d),a
	add    *(0x104d),a
	; @CCDA 8085 stl    a,*ar5
	stl    a,*ar5
	; @CCDB f272 rptbd  0xcce4
	rptbd  0xcce4
	; @CCDD 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CCDE 3193 mpya   *ar3+
	mpya   *ar3+
	; @CCDF bba5 mas    *ar4+,*ar3-,b
	mas    *ar4+,*ar3-,b
	; @CCE0 9d3e srccd  *ar5,bgt
	srccd  *ar5,bgt
	; @CCE1 9c9e strcd  *ar3+,bgt
	strcd  *ar3+,bgt
	; @CCE2 9e5e saccd  a,*ar3-,bgt
	saccd  a,*ar3-,bgt
	; @CCE3 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CCE4 3193 mpya   *ar3+
	mpya   *ar3+
	; @CCE5 6f79 ld     0x79,13,a
	ld     0x79,13,a
	; @CCE7 923d sub    *ar5,13,a
	sub    *ar5,13,a
	; @CCE8 6f13 sth    a,3,0x13
	sth    a,3,0x13
	; @CCEA 3177 mpya   0x77
	mpya   0x77
	; @CCEB 4009 sub    0x09,16,a
	sub    0x09,16,a
	; @CCEC 6ff8 add    *(0x104c),1,b
	add    *(0x104c),1,b
	; @CCEF 6f6e sth    b,15,0x6e
	sth    b,15,0x6e
	; @CCF1 f463 sfta   a,3
	sfta   a,3
	; @CCF2 3177 mpya   0x77
	mpya   0x77
	; @CCF3 6ff8 add    *(0x104d),1,b
	add    *(0x104d),1,b
	; @CCF6 6f6f sth    b,15,0x6f
	sth    b,15,0x6f
	; @CCF8 e734 mvmm   ar3,ar4
	mvmm   ar3,ar4
	; @CCF9 6deb mar    *+ar3(0x10fa)
	mar    *+ar3(0x10fa)
	; @CCFB 6dec mar    *+ar4(0x1060)
	mar    *+ar4(0x1060)
	; @CCFD 7711 stm    #4175,ar1
	stm    #4175,ar1
	; @CCFF 1084 ld     *ar4,a
	ld     *ar4,a
	; @CD00 8064 stl    a,0x64
	stl    a,0x64
	; @CD01 941f ld     *ar3,15,a
	ld     *ar3,15,a
	; @CD02 4e62 dst    a,0x62
	dst    a,0x62
	; @CD03 1081 ld     *ar1,a
	ld     *ar1,a
	; @CD04 0065 add    0x65,a
	add    0x65,a
	; @CD05 7712 stm    #120,ar2
	stm    #120,ar2
	; @CD07 7713 stm    #104,ar3
	stm    #104,ar3
	; @CD09 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD0A 8914 stlm   b,ar4
	stlm   b,ar4
	; @CD0B b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD0C 8915 stlm   b,ar5
	stlm   b,ar5
	; @CD0D b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD0E 8916 stlm   b,ar6
	stlm   b,ar6
	; @CD0F b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD10 8917 stlm   b,ar7
	stlm   b,ar7
	; @CD11 771a stm    #7,brc
	stm    #7,brc
	; @CD13 307b ld     0x7b,t
	ld     0x7b,t
	; @CD14 f272 rptbd  0xcd1c
	rptbd  0xcd1c
	; @CD16 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CD18 21dc mpy    *ar4+0%,b
	mpy    *ar4+0%,b
	; @CD19 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CD1A 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CD1B 29df mac    *ar7+0%,b
	mac    *ar7+0%,b
	; @CD1C 4f91 dst    b,*ar1+
	dst    b,*ar1+
	; @CD1D b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD1E 8914 stlm   b,ar4
	stlm   b,ar4
	; @CD1F b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD20 8915 stlm   b,ar5
	stlm   b,ar5
	; @CD21 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD22 8916 stlm   b,ar6
	stlm   b,ar6
	; @CD23 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD24 8917 stlm   b,ar7
	stlm   b,ar7
	; @CD25 10f8 ld     *(0x104f),a
	ld     *(0x104f),a
	; @CD27 0066 add    0x66,a
	add    0x66,a
	; @CD28 8812 stlm   a,ar2
	stlm   a,ar2
	; @CD29 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CD2B 771a stm    #7,brc
	stm    #7,brc
	; @CD2D 307b ld     0x7b,t
	ld     0x7b,t
	; @CD2E 20dc mpy    *ar4+0%,a
	mpy    *ar4+0%,a
	; @CD2F f272 rptbd  0xcd38
	rptbd  0xcd38
	; @CD31 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CD33 5091 dadd   *ar1+,a
	dadd   *ar1+,a
	; @CD34 90cc add    *ar2+0%,12,a
	add    *ar2+0%,12,a
	; @CD35 28dd mac    *ar5+0%,a
	mac    *ar5+0%,a
	; @CD36 28de mac    *ar6+0%,a
	mac    *ar6+0%,a
	; @CD37 2adf macr   *ar7+0%,a
	macr   *ar7+0%,a
	; @CD38 cce9 st     a,*ar3+ || mpy    *ar4+0%,a
	st     a,*ar3+ || mpy    *ar4+0%,a
	; @CD39 1067 ld     0x67,a
	ld     0x67,a
	; @CD3A 00f8 add    *(0x104e),a
	add    *(0x104e),a
	; @CD3C 8812 stlm   a,ar2
	stlm   a,ar2
	; @CD3D 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CD3F 4464 ld     0x64,16,a
	ld     0x64,16,a
	; @CD40 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CD41 ec06 rpt    #6
	rpt    #6
	; @CD42 c3c9 st     b,*ar3+ || add    *ar2+0%,b
	st     b,*ar3+ || add    *ar2+0%,b
	; @CD43 8383 sth    b,*ar3
	sth    b,*ar3
	; @CD44 3078 ld     0x78,t
	ld     0x78,t
	; @CD45 10f8 ld     *(0x104e),a
	ld     *(0x104e),a
	; @CD47 0065 add    0x65,a
	add    0x65,a
	; @CD48 7713 stm    #104,ar3
	stm    #104,ar3
	; @CD4A 7712 stm    #120,ar2
	stm    #120,ar2
	; @CD4C b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD4D 8914 stlm   b,ar4
	stlm   b,ar4
	; @CD4E b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD4F 8915 stlm   b,ar5
	stlm   b,ar5
	; @CD50 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD51 8916 stlm   b,ar6
	stlm   b,ar6
	; @CD52 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD53 8917 stlm   b,ar7
	stlm   b,ar7
	; @CD54 771a stm    #7,brc
	stm    #7,brc
	; @CD56 307c ld     0x7c,t
	ld     0x7c,t
	; @CD57 f272 rptbd  0xcd5f
	rptbd  0xcd5f
	; @CD59 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CD5B 21dc mpy    *ar4+0%,b
	mpy    *ar4+0%,b
	; @CD5C 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CD5D 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CD5E 29df mac    *ar7+0%,b
	mac    *ar7+0%,b
	; @CD5F 4f91 dst    b,*ar1+
	dst    b,*ar1+
	; @CD60 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD61 8914 stlm   b,ar4
	stlm   b,ar4
	; @CD62 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD63 8915 stlm   b,ar5
	stlm   b,ar5
	; @CD64 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD65 8916 stlm   b,ar6
	stlm   b,ar6
	; @CD66 b109 mac    *ar2,*ar3+,a,b
	mac    *ar2,*ar3+,a,b
	; @CD67 8917 stlm   b,ar7
	stlm   b,ar7
	; @CD68 0865 sub    0x65,a
	sub    0x65,a
	; @CD69 0066 add    0x66,a
	add    0x66,a
	; @CD6A 8812 stlm   a,ar2
	stlm   a,ar2
	; @CD6B 771a stm    #7,brc
	stm    #7,brc
	; @CD6D 307c ld     0x7c,t
	ld     0x7c,t
	; @CD6E 5662 dld    0x62,a
	dld    0x62,a
	; @CD6F f272 rptbd  0xcd7a
	rptbd  0xcd7a
	; @CD71 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CD73 6fda add    *ar2+0%,9,a,b
	add    *ar2+0%,9,a,b
	; @CD75 5381 dadd   *ar1,b
	dadd   *ar1,b
	; @CD76 29dc mac    *ar4+0%,b
	mac    *ar4+0%,b
	; @CD77 29dd mac    *ar5+0%,b
	mac    *ar5+0%,b
	; @CD78 29de mac    *ar6+0%,b
	mac    *ar6+0%,b
	; @CD79 29df mac    *ar7+0%,b
	mac    *ar7+0%,b
	; @CD7A 4f91 dst    b,*ar1+
	dst    b,*ar1+
	; @CD7B 7711 stm    #4175,ar1
	stm    #4175,ar1
	; @CD7D 1067 ld     0x67,a
	ld     0x67,a
	; @CD7E 0081 add    *ar1,a
	add    *ar1,a
	; @CD7F 8812 stlm   a,ar2
	stlm   a,ar2
	; @CD80 7713 stm    #4248,ar3
	stm    #4248,ar3
	; @CD82 771a stm    #7,brc
	stm    #7,brc
	; @CD84 e726 mvmm   ar2,ar6
	mvmm   ar2,ar6
	; @CD85 f272 rptbd  0xcd8e
	rptbd  0xcd8e
	; @CD87 7714 stm    #4192,ar4
	stm    #4192,ar4
	; @CD89 4493 ld     *ar3+,16,a
	ld     *ar3+,16,a
	; @CD8A 3dda add    *ar2+0%,16,a,b
	add    *ar2+0%,16,a,b
	; @CD8B ec06 rpt    #6
	rpt    #6
	; @CD8C c3ca st     b,*ar4+ || add    *ar2+0%,b
	st     b,*ar4+ || add    *ar2+0%,b
	; @CD8D 8394 sth    b,*ar4+
	sth    b,*ar4+
	; @CD8E e762 mvmm   ar6,ar2
	mvmm   ar6,ar2
	; @CD8F 1089 ld     *ar1-,a
	ld     *ar1-,a
	; @CD90 3081 ld     *ar1,t
	ld     *ar1,t
	; @CD91 2878 mac    0x78,a
	mac    0x78,a
	; @CD92 0065 add    0x65,a
	add    0x65,a
	; @CD93 8812 stlm   a,ar2
	stlm   a,ar2
	; @CD94 7711 stm    #4394,ar1
	stm    #4394,ar1
	; @CD96 7713 stm    #4176,ar3
	stm    #4176,ar3
	; @CD98 e737 mvmm   ar3,ar7
	mvmm   ar3,ar7
	; @CD99 7715 stm    #123,ar5
	stm    #123,ar5
	; @CD9B 771a stm    #7,brc
	stm    #7,brc
	; @CD9D f272 rptbd  0xcdbc
	rptbd  0xcdbc
	; @CD9F 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CDA1 5791 dld    *ar1+,b
	dld    *ar1+,b
	; @CDA2 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDA3 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDA4 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDA5 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDA6 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDA7 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDA8 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDA9 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDAA 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDAB b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDAC b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDAD 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDAE b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDAF b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDB0 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDB1 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDB2 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDB3 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDB4 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDB5 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDB6 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDB7 b29b mac    *ar3+,*ar5+,b,a
	mac    *ar3+,*ar5+,b,a
	; @CDB8 b4c7 macr   *ar2+0%,*ar5-,a
	macr   *ar2+0%,*ar5-,a
	; @CDB9 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @CDBA 6dea mar    *+ar2(0xa0)
	mar    *+ar2(0xa0)
	; @CDBC e773 mvmm   ar7,ar3
	mvmm   ar7,ar3
	; @CDBD 771a stm    #63,brc
	stm    #63,brc
	; @CDBF 7712 stm    #4192,ar2
	stm    #4192,ar2
	; @CDC1 7713 stm    #114,ar3
	stm    #114,ar3
	; @CDC3 7693 st     #1,*ar3+
	st     #1,*ar3+
	; @CDC5 768b st     #-1,*ar3-
	st     #-1,*ar3-
	; @CDC7 7714 stm    #4346,ar4
	stm    #4346,ar4
	; @CDC9 7715 stm    #118,ar5
	stm    #118,ar5
	; @CDCB 6ff8 ld     *(0x104e),3,a
	ld     *(0x104e),3,a
	; @CDCE 00f8 add    *(0x104f),a
	add    *(0x104f),a
	; @CDD0 8085 stl    a,*ar5
	stl    a,*ar5
	; @CDD1 f272 rptbd  0xcdda
	rptbd  0xcdda
	; @CDD3 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CDD4 3193 mpya   *ar3+
	mpya   *ar3+
	; @CDD5 bba5 mas    *ar4+,*ar3-,b
	mas    *ar4+,*ar3-,b
	; @CDD6 9d3e srccd  *ar5,bgt
	srccd  *ar5,bgt
	; @CDD7 9c9e strcd  *ar3+,bgt
	strcd  *ar3+,bgt
	; @CDD8 9e5e saccd  a,*ar3-,bgt
	saccd  a,*ar3-,bgt
	; @CDD9 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @CDDA 3193 mpya   *ar3+
	mpya   *ar3+
	; @CDDB 6f79 ld     0x79,13,a
	ld     0x79,13,a
	; @CDDD 923d sub    *ar5,13,a
	sub    *ar5,13,a
	; @CDDE 3177 mpya   0x77
	mpya   0x77
	; @CDDF 4009 sub    0x09,16,a
	sub    0x09,16,a
	; @CDE0 6ff8 add    *(0x104e),1,b
	add    *(0x104e),1,b
	; @CDE3 6f70 sth    b,15,0x70
	sth    b,15,0x70
	; @CDE5 f463 sfta   a,3
	sfta   a,3
	; @CDE6 3177 mpya   0x77
	mpya   0x77
	; @CDE7 6ff8 add    *(0x104f),1,b
	add    *(0x104f),1,b
	; @CDEA 6f71 sth    b,15,0x71
	sth    b,15,0x71
	; @CDEC 7714 stm    #4167,ar4
	stm    #4167,ar4
	; @CDEE 7715 stm    #4168,ar5
	stm    #4168,ar5
	; @CDF0 1184 ld     *ar4,b
	ld     *ar4,b
	; @CDF1 7712 stm    #116,ar2
	stm    #116,ar2
	; @CDF3 a485 mpy    *ar2+,*ar3-,a
	mpy    *ar2+,*ar3-,a
	; @CDF4 b809 mas    *ar2,*ar3+,a
	mas    *ar2,*ar3+,a
	; @CDF5 fa47 bcd    0xce00,aleq
	bcd    0xce00,aleq
	; @CDF7 ec07 rpt    #7
	rpt    #7
	; @CDF8 e5ba mvdd   *ar5+,*ar4+
	mvdd   *ar5+,*ar4+
	; @CDF9 e554 mvdd   *ar3-,*ar2-
	mvdd   *ar3-,*ar2-
	; @CDFA e510 mvdd   *ar3,*ar2
	mvdd   *ar3,*ar2
	; @CDFB 7712 stm    #4296,ar2
	stm    #4296,ar2
	; @CDFD ec09 rpt    #9
	rpt    #9
	; @CDFE 7092 mvkd   0x68,*ar2+
	mvkd   0x68,*ar2+
	; @CE00 8a11 popm   ar1
	popm   ar1
	; @CE01 8184 stl    b,*ar4
	stl    b,*ar4
	; @CE02 6c89 banz   0xca84,*ar1-
	banz   0xca84,*ar1-
	; @CE04 fc00 ret
	ret
