; ROM6 0x8413 SUB_8413 -- 32w, symbols.yaml data_word.
; Evidence: Entry F074 05A0 4915 F310 0003 F77F; callers 2x F074 @3551/@3802 verified; interior uncond b 843A @8431; shrunk bound 8413-8432 incl operand (linear exit ret 8448); HYPOTHESIS.
; ORIGIN 0x8413
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a0
	ldm    ar5,b
	sub    #3,b
	sfta   b,-1
	stlm   b,brc
	rc     blt
	cmpm   *(0x250f),#34
	bc     0x8436,ntc
	cmpm   *(0x34bf),#3
	bc     0x8436,ntc
	bitf   *(0x2648),#2048
	bc     0x8433,ntc
	stm    #9801,ar4
	stm    #13554,ar3
	andm   #-2049,*(0x2648)
	b      0x843a
