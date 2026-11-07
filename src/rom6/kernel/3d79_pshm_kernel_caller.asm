; ROM6 0x3D79 PSHM_KERNEL_CALLER -- 218w, symbols.yaml data_word.
; Evidence: Entry F074 063C; bound 3D79-3E52 (terminal RET raw+full-disasm); callers F074@A633/A64B/ABCF + F274@48EF/4918/A5EA; pshm prelude + pa33; HYPOTHESIS.
; ORIGIN 0x3D79
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @3D79 f074 call   0x63c
	call   0x63c
	; @3D7B 4a10 pshm   ar0
	pshm   ar0
	; @3D7C 4a08 pshm   al
	pshm   al
	; @3D7D 4a09 pshm   ah
	pshm   ah
	; @3D7E 4a0a pshm   ag
	pshm   ag
	; @3D7F 7710 stm    #9787,ar0
	stm    #9787,ar0
	; @3D81 f210 sub    #975,b,a
	sub    #975,b,a
	; @3D83 f310 sub    #124,b
	sub    #124,b
	.word 0xFF42 ; XC: gas encoder gap
	; @3D86 f120 ld     #-1,b
	ld     #-1,b
	; @3D88 f495 nop
	nop
	; @3D89 f495 nop
	nop
	; @3D8A 8a0a popm   ag
	popm   ag
	; @3D8B 8a09 popm   ah
	popm   ah
	; @3D8C 8a08 popm   al
	popm   al
	; @3D8D 6880 andm   #-5,*ar0
	andm   #-5,*ar0
	.word 0xFF4F ; XC: gas encoder gap
	; @3D90 6980 orm    #4,*ar0
	orm    #4,*ar0
	; @3D92 f130 and    #2,a,b
	and    #2,a,b
	; @3D94 f84d bc     0x3d98,beq
	bc     0x3d98,beq
	; @3D96 7313 mvmd   ar3,0x231
	mvmd   ar3,0x231
	; @3D98 7312 mvmd   ar2,0x230
	mvmd   ar2,0x230
	; @3D9A 7710 stm    #556,ar0
	stm    #556,ar0
	; @3D9C 8090 stl    a,*ar0+
	stl    a,*ar0+
	; @3D9D 61f8 bitf   *(0x3ec8),#32
	bitf   *(0x3ec8),#32
	; @3DA0 f110 sub    #1,a,b
	sub    #1,a,b
	; @3DA2 f820 bc     0x3da6,ntc
	bc     0x3da6,ntc
	; @3DA4 f84d bc     0x3da8,beq
	bc     0x3da8,beq
	; @3DA6 7080 mvkd   0x3e9a,*ar0
	mvkd   0x3e9a,*ar0
	; @3DA8 6d88 mar    *ar0-
	mar    *ar0-
	; @3DA9 1090 ld     *ar0+,a
	ld     *ar0+,a
	; @3DAA f130 and    #8,a,b
	and    #8,a,b
	; @3DAC f84d bc     0x3db5,beq
	bc     0x3db5,beq
	; @3DAE 76f8 st     #1,*(0x22f)
	st     #1,*(0x22f)
	; @3DB1 4488 ld     *ar0-,16,a
	ld     *ar0-,16,a
	; @3DB2 f074 call   0x3cd2
	call   0x3cd2
	; @3DB4 1080 ld     *ar0,a
	ld     *ar0,a
	; @3DB5 f130 and    #1,a,b
	and    #1,a,b
	; @3DB7 f84d bc     0x3dd5,beq
	bc     0x3dd5,beq
	; @3DB9 61f8 bitf   *(0x3ec8),#32
	bitf   *(0x3ec8),#32
	; @3DBC f820 bc     0x3dc6,ntc
	bc     0x3dc6,ntc
	; @3DBE f130 and    #8,a,b
	and    #8,a,b
	; @3DC0 f84c bc     0x3dc6,bneq
	bc     0x3dc6,bneq
	; @3DC2 44f8 ld     *(0x22d),16,a
	ld     *(0x22d),16,a
	; @3DC4 f074 call   0x3cd2
	call   0x3cd2
	; FORCED .word (ld     #128,b): dual-encoding rom=F120 got=E980
	.word 0xF120
	.word 0x0080
	; @3DC8 7710 stm    #1304,ar0
	stm    #1304,ar0
	; @3DCA 8190 stl    b,*ar0+
	stl    b,*ar0+
	; @3DCB 8190 stl    b,*ar0+
	stl    b,*ar0+
	; @3DCC f120 ld     #256,b
	ld     #256,b
	; @3DCE 8190 stl    b,*ar0+
	stl    b,*ar0+
	; @3DCF 8180 stl    b,*ar0
	stl    b,*ar0
	; @3DD0 68f8 andm   #-3,*(0x51d)
	andm   #-3,*(0x51d)
	; @3DD3 f073 b      0x3dfd
	b      0x3dfd
	; @3DD5 f110 sub    #2,a,b
	sub    #2,a,b
	; @3DD7 f84c bc     0x3df6,bneq
	bc     0x3df6,bneq
	; @3DD9 44f8 ld     *(0x2490),16,a
	ld     *(0x2490),16,a
	; @3DDB 71f8 mvdk   *(0x2490),0x22d
	mvdk   *(0x2490),0x22d
	; @3DDE 61f8 bitf   *(0x3ec8),#32
	bitf   *(0x3ec8),#32
	; @3DE1 f820 bc     0x3df2,ntc
	bc     0x3df2,ntc
	; @3DE3 60f8 cmpm   *(0x250f),#34
	cmpm   *(0x250f),#34
	; @3DE6 f820 bc     0x3df2,ntc
	bc     0x3df2,ntc
	; @3DE8 60f8 cmpm   *(0x34bf),#4
	cmpm   *(0x34bf),#4
	; @3DEB f820 bc     0x3df2,ntc
	bc     0x3df2,ntc
	; @3DED 44f8 ld     *(0x3491),16,a
	ld     *(0x3491),16,a
	; @3DEF 71f8 mvdk   *(0x3491),0x22d
	mvdk   *(0x3491),0x22d
	; @3DF2 f074 call   0x3cd2
	call   0x3cd2
	; @3DF4 f073 b      0x3dfd
	b      0x3dfd
	; @3DF6 f130 and    #4,a,b
	and    #4,a,b
	; @3DF8 f84d bc     0x3dfd,beq
	bc     0x3dfd,beq
	; @3DFA 76f8 st     #4,*(0x22e)
	st     #4,*(0x22e)
	; @3DFD 76f8 st     #1,*(0x22a)
	st     #1,*(0x22a)
	; @3E00 e900 ld     #0,b
	ld     #0,b
	; @3E01 7710 stm    #552,ar0
	stm    #552,ar0
	; @3E03 4f90 dst    b,*ar0+
	dst    b,*ar0+
	; @3E04 69f8 orm    #16,*(0x51d)
	orm    #16,*(0x51d)
	; @3E07 68f8 andm   #-2,*(0x51d)
	andm   #-2,*(0x51d)
	; @3E0A f074 call   0x25d9
	call   0x25d9
	; @3E0C 61f8 bitf   *(0x7),#2048
	bitf   *(0x7),#2048
	; @3E0F f7bb ssbx   st1,intm
	ssbx   st1,intm
	; @3E10 74f8 portr  33,*(0x8)
	portr  33,*(0x8)
	; @3E13 f040 or     #512,a
	or     #512,a
	; @3E15 f495 nop
	nop
	; @3E16 75f8 portw  *(0x8),33
	portw  *(0x8),33
	.word 0xFD20 ; XC: gas encoder gap
	; @3E1A f6bb rsbx   st1,intm
	rsbx   st1,intm
	; @3E1B 4911 ldm    ar1,b
	ldm    ar1,b
	; @3E1C 09f8 sub    *(0x3ea7),b
	sub    *(0x3ea7),b
	; @3E1E f84a bc     0x3e22,bgeq
	bc     0x3e22,bgeq
	; @3E20 01f8 add    *(0x36a),b
	add    *(0x36a),b
	; @3E22 f495 nop
	nop
	; @3E23 75f8 portw  *(0xb),10
	portw  *(0xb),10
	; @3E26 ec15 rpt    #21
	rpt    #21
	; @3E27 f495 nop
	nop
	; @3E28 f120 ld     #15000,b
	ld     #15000,b
	; @3E2A f495 nop
	nop
	; @3E2B 75f8 portw  *(0xb),11
	portw  *(0xb),11
	; @3E2E ec16 rpt    #22
	rpt    #22
	; @3E2F f495 nop
	nop
	; @3E30 f495 nop
	nop
	; @3E31 75f8 portw  *(0x11),9
	portw  *(0x11),9
	; @3E34 ec13 rpt    #19
	rpt    #19
	; @3E35 f495 nop
	nop
	; @3E36 61f8 bitf   *(0x7),#2048
	bitf   *(0x7),#2048
	; @3E39 f7bb ssbx   st1,intm
	ssbx   st1,intm
	; @3E3A 74f8 portr  43,*(0x8)
	portr  43,*(0x8)
	; @3E3D f040 or     #512,a
	or     #512,a
	; @3E3F f495 nop
	nop
	; @3E40 75f8 portw  *(0x8),43
	portw  *(0x8),43
	; @3E43 f495 nop
	nop
	; @3E44 74f8 portr  3,*(0x8)
	portr  3,*(0x8)
	; @3E47 f040 or     #5,a
	or     #5,a
	; @3E49 f495 nop
	nop
	; @3E4A 75f8 portw  *(0x8),3
	portw  *(0x8),3
	; @3E4D ec0e rpt    #14
	rpt    #14
	; @3E4E f495 nop
	nop
	.word 0xFD20 ; XC: gas encoder gap
	; @3E50 f6bb rsbx   st1,intm
	rsbx   st1,intm
	; @3E51 8a10 popm   ar0
	popm   ar0
	; @3E52 fc00 ret
	ret
