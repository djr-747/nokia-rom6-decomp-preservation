; ROM6 0x58E0 SUB_58E0 -- 37w, symbols.yaml data_word.
; Evidence: Entry F074 05FC; bound 58E0-5904 (FC00@5904); 4x F274 callers @5895/58A1 (objdump calld) + @593F/5954 (byte-verified F274 58E0); rptbd 5903 BK-style math (andm/or/xc), zero interio
; Pool: word 32F8@58F3 (disasm ld *(0xb),asm) matches no ti-c54x catalog row (nearest LD_ASM_SMEM 0x3280/FFE0 composes 32E0, MOD rows 32A0-32D0/FFF8 exclude 32F8); ASM shift-count dark in-span. Neighbors grounded (LD_SRC_SHIFT F55E row+leaf, LD_SRC_ASM F782 row+leaf, CMPL F793 row, ADD_SMEM_TS 0584 row+leaf) -- single-word blocker. stays .asm, bytes verified.
; ORIGIN 0x58E0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5fc
	stm    #96,ar2
	stm    #56,brc
	st     #64,*ar2+
	rptbd  0x5903
	st     #456,*ar2-
	ld     a,-2,b
	stlm   b,ar3
	and    #3,a,b
	sfta   b,2
	stlm   b,t
	add    *ar2+,a
	ld     *(0xb),asm
	ld     #15,b
	mar    *ar3+0
	ld     b,asm
	cmpl   b
	andm   #15,*ar4
	and    *ar3,b
	add    *ar4,ts,b
	stl    b,*ar3
	sub    *ar2-,a,b
	mar    *+ar4(0x2)
	xc     1,bgt
	ld     b,a
	ret
