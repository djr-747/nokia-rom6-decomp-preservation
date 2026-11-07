; ROM6 0xAA7C SEQ_AA7C -- 75w, symbols.yaml data_word.
; Evidence: Entry F074 06A4 F074 3EE1 11F8 057B; bound AA7C-AAC6 (exit FE00@AAC4 + slots to AAC6); caller F074@AB43 (objdump-verified); interior calls 06A4/3EE1 (PORT13_STABLE_READ); zero cond
; ORIGIN 0xAA7C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6a4
	call   0x3ee1
	ld     *(0x57b),b
	and    #16128,b
	sub    a,1,b
	sfta   b,-1
	neg    b
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
	xc     1,ageq
	ld     a,b
	neg    b
	ld     *(0x57b),a
	and    #-16384,a
	add    a,-14,b
	add    #8,b
	sfta   b,3,a
	add    #4,b
	and    #3,b
	stlm   b,t
	mpy    #80,b
	stlm   a,t
	sfta   b,15,a
	mpy    #25207,b
	sub    a,b
	ld     #0,a
	popm   ah
	sfta   a,1
	stm    #484,t
	mpya   a
	stm    #0,t
	add    a,-1,b
	add    #164,16,b
	macar  t,b
	neg    b
	add    *(0x1f3),16,b
	sub    #11264,16,b,a
	rc     ageq
	retd
	add    #632,16,b
