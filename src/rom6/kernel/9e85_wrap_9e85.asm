; ROM6 0x9E85 WRAP_9E85 -- 75w, symbols.yaml data_word.
; Evidence: Entry F074 06C6 61F8 085D 003F; callers F074@211C(objdump call)/A803; first-RET @0x9ECF (75w); HYPOTHESIS.
; ORIGIN 0x9E85
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6c6
	bitf   *(0x85d),#63
	rc     ntc
	bitf   *(0x4c2),#4
	rc     tc
	pshm   st1
	pshm   st0
	ssbx   st1,frct
	ssbx   st1,sxm
	ssbx   st1,ovm
	bitf   *(0x85d),#2
	bc     0x9ebd,ntc
	bitf   *(0x57c),#16384
	bc     0x9ea3,ntc
	call   0x9ed0
	andm   #-16385,*(0x57c)
	bitf   *(0x57c),#4096
	bc     0x9ebd,tc
	ld     *(0x57c),a
	and    #4095,a
	bc     0x9ebd,aleq
	ld     #0,b
	mvdm   0x57d,ar2
	calld  0x9d2d
	stm    #13014,ar3
	mvmd   ar2,0x57d
	addm   #-1,*(0x57c)
	orm    #4096,*(0x57c)
	call   0x6c6
	bitf   *(0x85d),#4
	bc     0x9ecd,ntc
	ld     *(0x57c),a
	and    #8192,a
	cc     0x9c99,aneq
	andm   #-8193,*(0x57c)
	popm   st0
	popm   st1
	ret
