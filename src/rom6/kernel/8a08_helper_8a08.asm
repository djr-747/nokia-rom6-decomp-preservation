; ROM6 0x8A08 HELPER_8A08 -- 50w, symbols.yaml data_word.
; Evidence: Entry F074 0592 7714 0008; bound 8A08-8A39 (FC00@8A39); caller F074@A752 (objdump-verified); interior F074 0592 + 4x F274 calld 8A3A @8A14/1C/22/28 (verified); HYPOTHESIS.
; ORIGIN 0x8A08
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x592
	stm    #8,ar4
	stm    #14,ar3
	ld     #0,b
	stm    #2506,ar2
	ld     *ar2+,16,a
	and    #-256,16,a
	calld  0x8a3a
	stl    b,*ar3
	or     *ar2+,a
	ld     *ar2+,16,a
	and    #-61,16,a
	or     *ar2+,a
	calld  0x8a3a
	andm   #-14337,*ar4
	ld     *ar2+,16,a
	or     *ar2+,a
	calld  0x8a3a
	andm   #-241,*ar4
	ld     *ar2+,16,a
	or     *ar2+,a
	calld  0x8a3a
	andm   #3,*ar4
	sub    #16,b
	ld     #0,a
	nop
	xc     1,blt
	ld     #1,a
	add    #14,b
	stm    #12419,ar2
	xc     1,blt
	ld     #2,a
	stl    a,*ar2
	ret
