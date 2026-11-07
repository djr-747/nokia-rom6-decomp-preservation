; ROM6 0x2DE4 ISR_2DE4 -- 75w, symbols.yaml data_word.
; Evidence: Entry F074 0628 12F8 0872 F845 2DF2 F074 2289; bound 2DE4-2E2E (abuts existing 2E2F); caller F074@2EB4; HPI ldu *(0x872/870/86E) + st #0 lanes + calls 0628/2289/B4F8/93CE; HYPOTHES
; ORIGIN 0x2DE4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x628
	ldu    *(0x872),a
	bc     0x2df2,aeq
	call   0x2289
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	ldu    *(0x870),a
	bc     0x2e02,aeq
	stlm   a,ar1
	call   0xb4f8
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	st     #0,*(0x870)
	bitf   *(0x54d),#8
	ldu    *(0x86e),a
	bc     0x2e2e,aeq
	bc     0x2e21,ntc
	stm    #12032,ar3
	st     #1024,*ar3+
	and    #255,a,b
	or     #256,b
	stl    b,*ar3+
	and    #-256,a
	stl    a,*ar3
	ld     #5,b
	stm    #12032,ar2
	ld     #20,a
	stm    #244,ar0
	call   0x93ce
	ldu    *(0x86e),a
	sfta   a,-8,b
	stlm   b,ar1
	and    #255,a
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	st     #0,*(0x86e)
	ret
