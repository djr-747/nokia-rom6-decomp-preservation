; ROM6 0x2B54 ISR_CTXSAVE_2B54 -- 77w, symbols.yaml program_word.
; Evidence: Fall-through from 2b53 COBBA cmd ISR entry (prev span); full pshm context save, flag strobes, dark 0xB4F8 call, orm/andm/st flag tail, balanced popm restores, frete; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x2B54
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #2,*(0x866)
	pshm   al
	pshm   ah
	pshm   ag
	pshm   bl
	pshm   bh
	pshm   bg
	ldu    *(0x870),a
	bc     0x2b98,aeq
	ld     *(0x4c2),a
	sub    #4,a
	bc     0x2b98,ageq
	pshd   *(0x60)
	pshd   *(0x61)
	pshm   t
	pshm   ar0
	pshm   ar1
	pshm   ar2
	pshm   ar3
	pshm   ar4
	pshm   ar5
	pshm   ar6
	pshm   ar7
	pshm   brc
	pshm   rsa
	pshm   rea
	pshm   bk
	stm    #0,rsa
	stm    #0,rea
	call   0xb4f8
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	st     #0,*(0x870)
	popm   bk
	popm   rea
	popm   rsa
	popm   brc
	popm   ar7
	popm   ar6
	popm   ar5
	popm   ar4
	popm   ar3
	popm   ar2
	popm   ar1
	popm   ar0
	popm   t
	popd   *(0x61)
	popd   *(0x60)
	popm   bg
	popm   bh
	popm   bl
	popm   ag
	popm   ah
	popm   al
	popm   st1
	popm   st0
	frete
