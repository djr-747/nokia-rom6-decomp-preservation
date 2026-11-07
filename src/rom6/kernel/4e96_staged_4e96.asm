; ROM6 0x4E96 STAGED_4E96 -- 38w, symbols.yaml data_word.
; Evidence: Entry F074 0670 7714 2F00 32F8 0016 7710 2F80; bound 4E96-4EBB; interior 4x calld 4EBC + calld 4F5F@4EB7 (objdump; 3 of 4 4EBC sites word-verified only); staged 2F00/2F80/2F21; HYP
; ORIGIN 0x4E96
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x670
	stm    #12032,ar4
	ld     *(0x16),asm
	stm    #12160,ar0
	calld  0x4ebc
	stm    #-9022,ar2
	mar    *ar4+
	calld  0x4ebc
	stm    #-8965,ar2
	mar    *ar4+
	stm    #12161,ar0
	calld  0x4ebc
	stm    #-9022,ar2
	mar    *ar4+
	calld  0x4ebc
	stm    #-8965,ar2
	stm    #12160,ar2
	stm    #1111,ar3
	calld  0x4f5f
	stm    #14,ar1
	ret
