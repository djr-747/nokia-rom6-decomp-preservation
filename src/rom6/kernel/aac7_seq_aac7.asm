; ROM6 0xAAC7 SEQ_AAC7 -- 94w, symbols.yaml data_word.
; Evidence: Entry F074 06A4 61F8 051C 0C00 45F8; bound AAC7-AB24 (exit FE00@AB22 + slots to AB24, largest of gap); caller F074@AB4C (objdump-verified); interior calls 06A4/3EE1; cond bc AAF0 a
; ORIGIN 0xAAC7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6a4
	bitf   *(0x51c),#3072
	ld     *(0x54a),16,b
	rc     tc
	call   0x3ee1
	pshm   al
	ld     *(0x57b),8,b
	and    #16128,b
	sub    a,1,b
	sfta   b,-1
	nop
	pshm   bl
	cmpm   *(0x250f),#33
	sub    #3800,a
	ld     *(0x914),b
	xc     2,ageq
	sub    #1,b
	xc     2,tc
	sub    #1,b
	sub    #13,b,a
	xc     2,blt
	add    #13,b
	bc     0xaaf0,alt
	ld     a,b
	ld     *(0x57b),8,a
	and    #-16384,a
	sub    a,-14,b
	sfta   b,3,a
	sub    #1,b
	and    #3,b
	stlm   b,t
	mpy    #80,b
	stlm   a,t
	mpy    #25207,a
	sub    b,15,a
	ld     a,b
	ld     #0,a
	popm   ah
	sfta   a,1
	stm    #484,t
	mpya   a
	stm    #0,t
	add    a,-1,b
	add    #124,16,b
	macar  t,b
	ld     #0,a
	popm   al
	cmpm   *(0x573),#-20649
	sub    #3800,a
	bc     0xab1b,ntc
	xc     2,ageq
	add    #160,16,b
	add    *(0x54b),16,b
	sub    #11896,16,b,a
	bc     0xab25,alt
	ld     a,b
	retd
	add    #11264,16,b
