; ROM6 0x7067 DIVSQRT_7067 -- 64w, symbols.yaml data_word.
; Evidence: Entry F074 0598; bound 7067-70A6 (FC00); callers F074 6C6E/6D0A/6D8E + F274 6E67/AC17(ext); subc- divide EC0F loop + sfta/norm tail; HYPOTHESIS.
; ORIGIN 0x7067
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @7067 f074 call   0x598
	call   0x598
	; @7069 61f8 bitf   *(0x51f),#128
	bitf   *(0x51f),#128
	; @706C f210 sub    #975,b,a
	sub    #975,b,a
	; @706E f842 bc     0x7077,ageq
	bc     0x7077,ageq
	; @7070 f310 sub    #512,b
	sub    #512,b
	; @7072 f820 bc     0x7077,ntc
	bc     0x7077,ntc
	.word 0xFF4A ; XC: gas encoder gap
	; @7075 7713 stm    #16099,ar3
	stm    #16099,ar3
	; @7077 e880 ld     #128,a
	ld     #128,a
	; @7078 1182 ld     *ar2,b
	ld     *ar2,b
	; @7079 fa4d bcd    0x7098,beq
	bcd    0x7098,beq
	; @707B 770e stm    #0,t
	stm    #0,t
	; @707D 4494 ld     *ar4+,16,a
	ld     *ar4+,16,a
	; @707E 1a8c or     *ar4-,a
	or     *ar4-,a
	; @707F 34f8 bitt   *(0x9)
	bitt   *(0x9)
	; @7081 f485 abs    a
	abs    a
	; @7082 f47c sfta   a,-4
	sfta   a,-4
	; @7083 ec0f rpt    #15
	rpt    #15
	; @7084 1e82 subc   *ar2,a
	subc   *ar2,a
	; @7085 f468 sfta   a,8
	sfta   a,8
	; @7086 f468 sfta   a,8
	sfta   a,8
	; @7087 770a stm    #0,ag
	stm    #0,ag
	.word 0xFD30 ; XC: gas encoder gap
	; @708A f484 neg    a
	neg    a
	; @708B 4583 ld     *ar3,16,b
	ld     *ar3,16,b
	; @708C f77c sfta   b,-4
	sfta   b,-4
	; @708D 76f8 st     #0,*(0xb)
	st     #0,*(0xb)
	; @7090 f620 sub    b,a
	sub    b,a
	; @7091 f47e sfta   a,-2
	sfta   a,-2
	; @7092 f001 add    #16384,1,a
	add    #16384,1,a
	; @7094 76f8 st     #0,*(0x8)
	st     #0,*(0x8)
	; @7097 f470 sfta   a,-16
	sfta   a,-16
	; @7098 f130 and    #255,a,b
	and    #255,a,b
	; @709A 8960 stlm   b,96
	stlm   b,96
	; @709B f768 sfta   b,8
	sfta   b,8
	; @709C f495 nop
	nop
	; @709D f495 nop
	nop
	; @709E 61f8 bitf   *(0x60),#128
	bitf   *(0x60),#128
	; @70A1 f830 bc     0x70a6,tc
	bc     0x70a6,tc
	; @70A3 76f8 st     #128,*(0x60)
	st     #128,*(0x60)
	; @70A6 fc00 ret
	ret
