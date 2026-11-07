; ROM6 0xC5F9 CONFIG_DISPATCH_C5F9 -- 103w, symbols.yaml data_word.
; Evidence: Entry F074 0692; bitf gates 0x51C/0x2B08/0x577/0x2AEE; calls 0xC5D2 + ccd 0x696/0x69E; first-RET @0xC65F (len 103); 3 F074 callers A6D6 A8EE AA05; HYPOTHESIS config dispatch.
; ORIGIN 0xC5F9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x692
	bitf   *(0x51c),#3072
	rc     tc
	pshm   st1
	rsbx   st1,ovm
	ssbx   st1,frct
	ld     #0,asm
	stm    #0,bk
	bitf   *(0x2b08),#3
	bc     0xc65e,ntc
	bitf   *(0x51c),#4096
	bc     0xc645,tc
	bitf   *(0x577),#768
	bc     0xc654,ntc
	bitf   *(0x2aee),#1
	bc     0xc645,tc
	mvdm   0x337c,ar2
	stm    #4709,ar3
	stm    #16151,ar4
	calld  0xc5c3
	stm    #159,brc
	ld     *(0x572),a
	mvdm   0x1266,ar6
	xc     2,aneq
	stm    #0,ar6
	rsbx   st1,sxm
	bitf   *(0x2213),#1
	bc     0xc63c,tc
	stm    #-18945,ar5
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 4
	mvdk   *ar5+,0x11
	call   0xc5d2
	calld  0xc5d2
	stm    #8743,ar1
	stm    #-18940,ar5
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 4
	mvdk   *ar5+,0x11
	call   0xc5d2
	ssbx   st1,sxm
	mvdm   0x337c,ar2
	stm    #8722,ar3
	stm    #4708,ar4
	stm    #4712,ar5
	bitf   *(0x577),#256
	ccd    0x696,tc
	stm    #159,brc
	ld     *(0x224f),-8,a
	bitf   *(0x577),#2
	ccd    0x69e,tc
	mvdm   0x337c,ar1
	popm   st1
	ret
