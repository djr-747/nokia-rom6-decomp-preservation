; ROM6 0x8C0A SUPERBLOCK_8C0A -- 465w, symbols.yaml data_word.
; Evidence: 0612-prologue head; first-RET @0x8DDA (len 465, longest in span); 2 callers 9CB8 A72C; 19 inner F074/F274 sites incl 4x to 0x8F7A hub (8D3C/8D59/8D77/8D90) plus 0x8DDB/0x8DDC/0x8E0
; ORIGIN 0x8C0A
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @8C0A f074 call   0x612
	call   0x612
	; @8C0C 4a07 pshm   st1
	pshm   st1
	; @8C0D f6be rsbx   st1,cpl
	rsbx   st1,cpl
	; @8C0E f7b9 ssbx   st1,ovm
	ssbx   st1,ovm
	; @8C0F f7b6 ssbx   st1,frct
	ssbx   st1,frct
	; @8C10 ed00 ld     #0,asm
	ld     #0,asm
	; @8C11 ea5e ld     #94,dp
	ld     #94,dp
	; @8C12 7620 st     #1,0x20
	st     #1,0x20
	; @8C14 7714 stm    #12157,ar4
	stm    #12157,ar4
	; @8C16 7712 stm    #12157,ar2
	stm    #12157,ar2
	; @8C18 7713 stm    #4099,ar3
	stm    #4099,ar3
	; @8C1A e800 ld     #0,a
	ld     #0,a
	; @8C1B 771a stm    #159,brc
	stm    #159,brc
	; @8C1D f272 rptbd  0x8c25
	rptbd  0x8c25
	; @8C1F 770e stm    #-28180,t
	stm    #-28180,t
	; @8C21 4594 ld     *ar4+,16,b
	ld     *ar4+,16,b
	; @8C22 d711 st     b,*ar3 || macr   *ar3,b
	st     b,*ar3 || macr   *ar3,b
	; @8C23 8392 sth    b,*ar2+
	sth    b,*ar2+
	; @8C24 f785 abs    b
	abs    b
	; @8C25 f486 max    a
	max    a
	; @8C26 e900 ld     #0,b
	ld     #0,b
	; @8C27 f845 bc     0x8c2d,aeq
	bc     0x8c2d,aeq
	; @8C29 f48e exp    a
	exp    a
	; @8C2A e904 ld     #4,b
	ld     #4,b
	; @8C2B 480e ldm    t,a
	ldm    t,a
	; @8C2C f520 sub    a,b
	sub    a,b
	; @8C2D 8122 stl    b,0x22
	stl    b,0x22
	; @8C2E f84f bc     0x8c3f,bleq
	bc     0x8c3f,bleq
	; @8C30 0920 sub    0x20,b
	sub    0x20,b
	; @8C31 f784 neg    b
	neg    b
	; @8C32 890e stlm   b,t
	stlm   b,t
	; @8C33 7621 st     #16384,0x21
	st     #16384,0x21
	; @8C35 1421 ld     0x21,ts,a
	ld     0x21,ts,a
	; @8C36 880e stlm   a,t
	stlm   a,t
	; @8C37 771a stm    #159,brc
	stm    #159,brc
	; @8C39 f272 rptbd  0x8c3e
	rptbd  0x8c3e
	; @8C3B 7712 stm    #12157,ar2
	stm    #12157,ar2
	; @8C3D 2282 mpyr   *ar2,a
	mpyr   *ar2,a
	; @8C3E 8292 sth    a,*ar2+
	sth    a,*ar2+
	; @8C3F 7712 stm    #12157,ar2
	stm    #12157,ar2
	; @8C41 2692 squr   *ar2+,a
	squr   *ar2+,a
	; @8C42 771a stm    #158,brc
	stm    #158,brc
	; @8C44 f272 rptbd  0x8c48
	rptbd  0x8c48
	; @8C46 7714 stm    #12400,ar4
	stm    #12400,ar4
	; @8C48 3892 squra  *ar2+,a
	squra  *ar2+,a
	; @8C49 4e94 dst    a,*ar4+
	dst    a,*ar4+
	; @8C4A f48e exp    a
	exp    a
	; @8C4B 7710 stm    #-158,ar0
	stm    #-158,ar0
	; @8C4D 8c21 st     t,0x21
	st     t,0x21
	; @8C4E e99c ld     #156,b
	ld     #156,b
	; @8C4F 891a stlm   b,brc
	stlm   b,brc
	; @8C50 7712 stm    #12158,ar2
	stm    #12158,ar2
	; @8C52 7713 stm    #12157,ar3
	stm    #12157,ar3
	; @8C54 7715 stm    #7,ar5
	stm    #7,ar5
	; @8C56 7719 stm    #0,bk
	stm    #0,bk
	; @8C58 f272 rptbd  0x8c5c
	rptbd  0x8c5c
	; @8C5A a489 mpy    *ar2+,*ar3+,a
	mpy    *ar2+,*ar3+,a
	; @8C5B 0920 sub    0x20,b
	sub    0x20,b
	; @8C5C b089 mac    *ar2+,*ar3+,a
	mac    *ar2+,*ar3+,a
	; @8C5D 6d90 mar    *ar0+
	mar    *ar0+
	; @8C5E b0c1 mac    *ar2+0%,*ar3,a
	mac    *ar2+0%,*ar3,a
	; @8C5F 4e94 dst    a,*ar4+
	dst    a,*ar4+
	; @8C60 891a stlm   b,brc
	stlm   b,brc
	; @8C61 6e8d banzd  0x8c58,*ar5-
	banzd  0x8c58,*ar5-
	; @8C63 7713 stm    #12157,ar3
	stm    #12157,ar3
	; @8C65 1122 ld     0x22,b
	ld     0x22,b
	; @8C66 7712 stm    #12157,ar2
	stm    #12157,ar2
	.word 0xFF4F ; XC: gas encoder gap
	; @8C69 7622 st     #0,0x22
	st     #0,0x22
	; @8C6B 771a stm    #159,brc
	stm    #159,brc
	; @8C6D f272 rptbd  0x8c71
	rptbd  0x8c71
	; @8C6F 3222 ld     0x22,asm
	ld     0x22,asm
	; @8C70 4492 ld     *ar2+,16,a
	ld     *ar2+,16,a
	; @8C71 c880 st     a,*ar2 || ld     *ar2+,a
	st     a,*ar2 || ld     *ar2+,a
	; @8C72 ed00 ld     #0,asm
	ld     #0,asm
	; @8C73 3021 ld     0x21,t
	ld     0x21,t
	; @8C74 7712 stm    #12086,ar2
	stm    #12086,ar2
	; @8C76 771a stm    #8,brc
	stm    #8,brc
	; @8C78 f272 rptbd  0x8c7e
	rptbd  0x8c7e
	; @8C7A 7713 stm    #12400,ar3
	stm    #12400,ar3
	; @8C7C 5693 dld    *ar3+,a
	dld    *ar3+,a
	; @8C7D f48f norm   a
	norm   a
	; @8C7E 8292 sth    a,*ar2+
	sth    a,*ar2+
	; @8C7F 7712 stm    #12077,ar2
	stm    #12077,ar2
	; @8C81 ec06 rpt    #6
	rpt    #6
	; @8C82 708a mvkd   0x2f37,*ar2-
	mvkd   0x2f37,*ar2-
	; @8C84 4a06 pshm   st0
	pshm   st0
	; @8C85 4a07 pshm   st1
	pshm   st1
	; @8C86 11f8 ld     *(0x2f22),b
	ld     *(0x2f22),b
	; @8C88 f074 call   0x5b2
	call   0x5b2
	; @8C8A 61f8 bitf   *(0x58f),#15
	bitf   *(0x58f),#15
	; @8C8D f820 bc     0x8c92,ntc
	bc     0x8c92,ntc
	; @8C8F e901 ld     #1,b
	ld     #1,b
	; @8C90 f073 b      0x8c96
	b      0x8c96
	; @8C92 f274 calld  0x8fae
	calld  0x8fae
	; @8C94 7711 stm    #12400,ar1
	stm    #12400,ar1
	; @8C96 81f8 stl    b,*(0x2f03)
	stl    b,*(0x2f03)
	; @8C98 8a07 popm   st1
	popm   st1
	; @8C99 8a06 popm   st0
	popm   st0
	; @8C9A 7710 stm    #2,ar0
	stm    #2,ar0
	; @8C9C 7713 stm    #12078,ar3
	stm    #12078,ar3
	; @8C9E 7715 stm    #7,ar5
	stm    #7,ar5
	; @8CA0 770e stm    #0,t
	stm    #0,t
	; @8CA2 7622 st     #22118,0x22
	st     #22118,0x22
	; @8CA4 7623 st     #31130,0x23
	st     #31130,0x23
	; @8CA6 7600 st     #11059,0x00
	st     #11059,0x00
	; @8CA8 7602 st     #26112,0x02
	st     #26112,0x02
	; @8CAA 7712 stm    #12086,ar2
	stm    #12086,ar2
	; @8CAC 7714 stm    #12077,ar4
	stm    #12077,ar4
	; @8CAE 4492 ld     *ar2+,16,a
	ld     *ar2+,16,a
	; @8CAF fa45 bcd    0x8cea,aeq
	bcd    0x8cea,aeq
	; @8CB1 9600 bit    *ar2,0
	bit    *ar2,0
	; @8CB2 458a ld     *ar2-,16,b
	ld     *ar2-,16,b
	; @8CB3 f785 abs    b
	abs    b
	; @8CB4 f84d bc     0x8cc5,beq
	bc     0x8cc5,beq
	; @8CB6 f620 sub    b,a
	sub    b,a
	; @8CB7 f843 bc     0x8cea,alt
	bc     0x8cea,alt
	; @8CB9 fa45 bcd    0x8cc0,aeq
	bcd    0x8cc0,aeq
	; @8CBB f020 ld     #32767,a
	ld     #32767,a
	; @8CBD f67f sfta   b,-1,a
	sfta   b,-1,a
	; @8CBE ec0f rpt    #15
	rpt    #15
	; @8CBF 1e82 subc   *ar2,a
	subc   *ar2,a
	; @8CC0 fa30 bcd    0x8cc5,tc
	bcd    0x8cc5,tc
	; @8CC2 8021 stl    a,0x21
	stl    a,0x21
	; @8CC3 1021 ld     0x21,a
	ld     0x21,a
	; @8CC4 f484 neg    a
	neg    a
	; @8CC5 880e stlm   a,t
	stlm   a,t
	; @8CC6 4915 ldm    ar5,b
	ldm    ar5,b
	; @8CC7 fa4d bcd    0x8cd5,beq
	bcd    0x8cd5,beq
	; @8CC9 0920 sub    0x20,b
	sub    0x20,b
	; @8CCA 891a stlm   b,brc
	stlm   b,brc
	; @8CCB 4592 ld     *ar2+,16,b
	ld     *ar2+,16,b
	; @8CCC 2b8a macr   *ar2-,b
	macr   *ar2-,b
	; @8CCD f272 rptbd  0x8cd4
	rptbd  0x8cd4
	; @8CCF 83b2 sth    b,*ar2+0
	sth    b,*ar2+0
	; @8CD0 448a ld     *ar2-,16,a
	ld     *ar2-,16,a
	; @8CD1 2a84 macr   *ar4,a
	macr   *ar4,a
	; @8CD2 c828 st     a,*ar2+ || ld     *ar4,a
	st     a,*ar2+ || ld     *ar4,a
	; @8CD3 2a92 macr   *ar2+,a
	macr   *ar2+,a
	; @8CD4 c846 st     a,*ar4- || ld     *ar2-,a
	st     a,*ar4- || ld     *ar2-,a
	; @8CD5 8c83 st     t,*ar3
	st     t,*ar3
	; @8CD6 4483 ld     *ar3,16,a
	ld     *ar3,16,a
	; @8CD7 9610 bit    *ar3,0
	bit    *ar3,0
	; @8CD8 f485 abs    a
	abs    a
	; @8CD9 4122 sub    0x22,16,a,b
	sub    0x22,16,a,b
	; @8CDA f84b bc     0x8ce3,blt
	bc     0x8ce3,blt
	; @8CDC 4123 sub    0x23,16,a,b
	sub    0x23,16,a,b
	; @8CDD f84b bc     0x8ce9,blt
	bc     0x8ce9,blt
	; @8CDF f273 bd     0x8cea
	bd     0x8cea
	; @8CE1 4002 sub    0x02,16,a
	sub    0x02,16,a
	; @8CE2 f462 sfta   a,2
	sfta   a,2
	; @8CE3 f063 and    #-2,16,a
	and    #-2,16,a
	; @8CE5 f273 bd     0x8cea
	bd     0x8cea
	; @8CE7 f47f sfta   a,-1
	sfta   a,-1
	; @8CE8 f495 nop
	nop
	; @8CE9 4000 sub    0x00,16,a
	sub    0x00,16,a
	.word 0xFD30 ; XC: gas encoder gap
	; @8CEB f484 neg    a
	neg    a
	; @8CEC 8293 sth    a,*ar3+
	sth    a,*ar3+
	; @8CED 6e8d banzd  0x8caa,*ar5-
	banzd  0x8caa,*ar5-
	; @8CEF 770e stm    #0,t
	stm    #0,t
	; @8CF1 7210 mvdm   0x551,ar0
	mvdm   0x551,ar0
	; @8CF3 7714 stm    #4538,ar4
	stm    #4538,ar4
	; @8CF5 6db4 mar    *ar4+0
	mar    *ar4+0
	; @8CF6 4910 ldm    ar0,b
	ldm    ar0,b
	; @8CF7 f300 add    #8,b
	add    #8,b
	; @8CF9 f330 and    #31,b
	and    #31,b
	; @8CFB 81f8 stl    b,*(0x551)
	stl    b,*(0x551)
	; @8CFD 7710 stm    #12432,ar0
	stm    #12432,ar0
	; @8CFF 7712 stm    #-19530,ar2
	stm    #-19530,ar2
	; @8D01 7713 stm    #12078,ar3
	stm    #12078,ar3
	; @8D03 7716 stm    #-19498,ar6
	stm    #-19498,ar6
	; @8D05 771a stm    #7,brc
	stm    #7,brc
	; @8D07 f272 rptbd  0x8d23
	rptbd  0x8d23
	; @8D09 7715 stm    #-19522,ar5
	stm    #-19522,ar5
	; @8D0B e51a mvdd   *ar3,*ar4+
	mvdd   *ar3,*ar4+
	; @8D0C 45e2 ld     *ar2(0x10),16,b
	ld     *ar2(0x10),16,b
	; @8D0E b281 mac    *ar2+,*ar3,b,a
	mac    *ar2+,*ar3,b,a
	; @8D0F f060 add    #256,16,a
	add    #256,16,a
	; @8D11 f477 sfta   a,-9
	sfta   a,-9
	; @8D12 f470 sfta   a,-16
	sfta   a,-16
	; @8D13 1196 ld     *ar6+,b
	ld     *ar6+,b
	; @8D14 f487 min    a
	min    a
	; @8D15 1195 ld     *ar5+,b
	ld     *ar5+,b
	; @8D16 f486 max    a
	max    a
	; @8D17 f620 sub    b,a
	sub    b,a
	; @8D18 8090 stl    a,*ar0+
	stl    a,*ar0+
	; @8D19 f500 add    a,b
	add    a,b
	; @8D1A f76a sfta   b,10
	sfta   b,10
	; @8D1B 10e2 ld     *ar2(0xf),a
	ld     *ar2(0xf),a
	; @8D1D f521 sub    a,1,b
	sub    a,1,b
	; @8D1E 890e stlm   b,t
	stlm   b,t
	; @8D1F f495 nop
	nop
	; @8D20 23e2 mpyr   *ar2(0x17),b
	mpyr   *ar2(0x17),b
	; @8D22 f700 add    b
	add    b
	; @8D23 8393 sth    b,*ar3+
	sth    b,*ar3+
	; @8D24 7601 st     #20070,0x01
	st     #20070,0x01
	; @8D26 7712 stm    #4100,ar2
	stm    #4100,ar2
	; @8D28 ec07 rpt    #7
	rpt    #7
	; @8D29 7192 mvdk   *ar2+,0x2f60
	mvdk   *ar2+,0x2f60
	; @8D2B 7712 stm    #12078,ar2
	stm    #12078,ar2
	; @8D2D 7713 stm    #4108,ar3
	stm    #4108,ar3
	; @8D2F 7714 stm    #12095,ar4
	stm    #12095,ar4
	; @8D31 771a stm    #7,brc
	stm    #7,brc
	; @8D33 f272 rptbd  0x8d3b
	rptbd  0x8d3b
	; @8D35 770e stm    #-2,t
	stm    #-2,t
	; @8D37 1492 ld     *ar2+,ts,a
	ld     *ar2+,ts,a
	; @8D38 0483 add    *ar3,ts,a
	add    *ar3,ts,a
	; @8D39 1193 ld     *ar3+,b
	ld     *ar3+,b
	; @8D3A f61f add    b,-1,a
	add    b,-1,a
	; @8D3B 8094 stl    a,*ar4+
	stl    a,*ar4+
	; @8D3C f274 calld  0x8f7a
	calld  0x8f7a
	; @8D3E 7712 stm    #12095,ar2
	stm    #12095,ar2
	; @8D40 7713 stm    #12158,ar3
	stm    #12158,ar3
	; @8D42 7714 stm    #12128,ar4
	stm    #12128,ar4
	; @8D44 7715 stm    #12136,ar5
	stm    #12136,ar5
	; @8D46 f274 calld  0x8ddb
	calld  0x8ddb
	; @8D48 771a stm    #12,brc
	stm    #12,brc
	; @8D4A 7712 stm    #12078,ar2
	stm    #12078,ar2
	; @8D4C 7713 stm    #4108,ar3
	stm    #4108,ar3
	; @8D4E 7714 stm    #12095,ar4
	stm    #12095,ar4
	; @8D50 771a stm    #7,brc
	stm    #7,brc
	; @8D52 f272 rptbd  0x8d58
	rptbd  0x8d58
	; @8D54 770e stm    #-1,t
	stm    #-1,t
	; @8D56 1492 ld     *ar2+,ts,a
	ld     *ar2+,ts,a
	; @8D57 0493 add    *ar3+,ts,a
	add    *ar3+,ts,a
	; @8D58 8094 stl    a,*ar4+
	stl    a,*ar4+
	; @8D59 f274 calld  0x8f7a
	calld  0x8f7a
	; @8D5B 7712 stm    #12095,ar2
	stm    #12095,ar2
	; @8D5D 7713 stm    #12172,ar3
	stm    #12172,ar3
	; @8D5F 7714 stm    #12136,ar4
	stm    #12136,ar4
	; @8D61 4421 ld     0x21,16,a
	ld     0x21,16,a
	; @8D62 f274 calld  0x8ddc
	calld  0x8ddc
	; @8D64 771a stm    #13,brc
	stm    #13,brc
	; @8D66 7712 stm    #12078,ar2
	stm    #12078,ar2
	; @8D68 7713 stm    #4108,ar3
	stm    #4108,ar3
	; @8D6A 7714 stm    #12095,ar4
	stm    #12095,ar4
	; @8D6C 771a stm    #7,brc
	stm    #7,brc
	; @8D6E f272 rptbd  0x8d76
	rptbd  0x8d76
	; @8D70 770e stm    #-2,t
	stm    #-2,t
	; @8D72 1482 ld     *ar2,ts,a
	ld     *ar2,ts,a
	; @8D73 0493 add    *ar3+,ts,a
	add    *ar3+,ts,a
	; @8D74 1192 ld     *ar2+,b
	ld     *ar2+,b
	; @8D75 f61f add    b,-1,a
	add    b,-1,a
	; @8D76 8094 stl    a,*ar4+
	stl    a,*ar4+
	; @8D77 f274 calld  0x8f7a
	calld  0x8f7a
	; @8D79 7712 stm    #12095,ar2
	stm    #12095,ar2
	; @8D7B 7713 stm    #12186,ar3
	stm    #12186,ar3
	; @8D7D 7714 stm    #12136,ar4
	stm    #12136,ar4
	; @8D7F 4421 ld     0x21,16,a
	ld     0x21,16,a
	; @8D80 f274 calld  0x8ddc
	calld  0x8ddc
	; @8D82 771a stm    #12,brc
	stm    #12,brc
	; @8D84 7712 stm    #12078,ar2
	stm    #12078,ar2
	; @8D86 7713 stm    #4108,ar3
	stm    #4108,ar3
	; @8D88 771a stm    #7,brc
	stm    #7,brc
	; @8D8A f272 rptbd  0x8d8f
	rptbd  0x8d8f
	; @8D8C 7714 stm    #12095,ar4
	stm    #12095,ar4
	; @8D8E e50a mvdd   *ar2,*ar4+
	mvdd   *ar2,*ar4+
	; @8D8F e589 mvdd   *ar2+,*ar3+
	mvdd   *ar2+,*ar3+
	; @8D90 f274 calld  0x8f7a
	calld  0x8f7a
	; @8D92 7712 stm    #12095,ar2
	stm    #12095,ar2
	; @8D94 7713 stm    #12199,ar3
	stm    #12199,ar3
	; @8D96 7714 stm    #12128,ar4
	stm    #12128,ar4
	; @8D98 4421 ld     0x21,16,a
	ld     0x21,16,a
	; @8D99 f274 calld  0x8ddc
	calld  0x8ddc
	; @8D9B 771a stm    #119,brc
	stm    #119,brc
	; @8D9D 7712 stm    #12128,ar2
	stm    #12128,ar2
	; @8D9F ec07 rpt    #7
	rpt    #7
	; @8DA0 7192 mvdk   *ar2+,0x1004
	mvdk   *ar2+,0x1004
	; @8DA2 7644 st     #-7,0x44
	st     #-7,0x44
	; @8DA4 7782 stm    #-19486,130
	stm    #-19486,130
	; @8DA6 f071 rptz   a,#4
	rptz   a,#4
	; @8DA8 7308 mvmd   al,0x2f78
	mvmd   al,0x2f78
	; @8DAA f274 calld  0x8e05
	calld  0x8e05
	; @8DAC 7715 stm    #12159,ar5
	stm    #12159,ar5
	; @8DAE f274 calld  0x8e88
	calld  0x8e88
	; @8DB0 7715 stm    #12440,ar5
	stm    #12440,ar5
	; @8DB2 f274 calld  0x8e05
	calld  0x8e05
	; @8DB4 7715 stm    #12199,ar5
	stm    #12199,ar5
	; @8DB6 f274 calld  0x8e88
	calld  0x8e88
	; @8DB8 7715 stm    #12457,ar5
	stm    #12457,ar5
	; @8DBA f274 calld  0x8e05
	calld  0x8e05
	; @8DBC 7715 stm    #12239,ar5
	stm    #12239,ar5
	; @8DBE f274 calld  0x8e88
	calld  0x8e88
	; @8DC0 7715 stm    #12474,ar5
	stm    #12474,ar5
	; @8DC2 f274 calld  0x8e05
	calld  0x8e05
	; @8DC4 7715 stm    #12279,ar5
	stm    #12279,ar5
	; @8DC6 f274 calld  0x8e88
	calld  0x8e88
	; @8DC8 7715 stm    #12491,ar5
	stm    #12491,ar5
	; @8DCA 7715 stm    #12440,ar5
	stm    #12440,ar5
	; @8DCC 7710 stm    #17,ar0
	stm    #17,ar0
	; @8DCE ec03 rpt    #3
	rpt    #3
	; @8DCF 71b5 mvdk   *ar5+0,0x2f13
	mvdk   *ar5+0,0x2f13
	; @8DD1 4a06 pshm   st0
	pshm   st0
	; @8DD2 4a07 pshm   st1
	pshm   st1
	; @8DD3 fb81 fcalld 0x1a776
	fcalld 0x1a776
	; @8DD5 7712 stm    #12051,ar2
	stm    #12051,ar2
	; @8DD7 8a07 popm   st1
	popm   st1
	; @8DD8 8a06 popm   st0
	popm   st0
	; @8DD9 8a07 popm   st1
	popm   st1
	; @8DDA fc00 ret
	ret
