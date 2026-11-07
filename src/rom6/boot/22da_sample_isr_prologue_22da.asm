; ROM6 0x22DA SAMPLE_ISR_PROLOGUE_22DA -- 23w, symbols.yaml program_word.
; Evidence: V16/INT0 entry (runtime IVT image V16 FB 0x22DA per roms/rom6/ivt.md; mask vector FFC0 fb 0x22DA in kernel/ffc0_vectors_ffc0.asm); CALL 0x05DA (mini-kernel, zeros in-mask, extern) then full pshm context save + STM #0,RSA (2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word is the 0x0000 immediate, not a dumped zero); span ends at the instruction boundary, 22F1 slot abuts.
; ORIGIN 0x22DA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5da ; @0x22DA f074
	pshm   st1 ; @0x22DC 4a07
	pshm   al ; @0x22DD 4a08
	pshm   ah ; @0x22DE 4a09
	pshm   ag ; @0x22DF 4a0a
	pshm   bl ; @0x22E0 4a0b
	pshm   bh ; @0x22E1 4a0c
	pshm   bg ; @0x22E2 4a0d
	pshm   t ; @0x22E3 4a0e
	pshm   ar1 ; @0x22E4 4a11
	pshm   ar6 ; @0x22E5 4a16
	pshm   ar0 ; @0x22E6 4a10
	pshm   ar4 ; @0x22E7 4a14
	pshm   ar5 ; @0x22E8 4a15
	pshm   ar2 ; @0x22E9 4a12
	pshm   ar3 ; @0x22EA 4a13
	pshm   brc ; @0x22EB 4a1a
	pshm   rsa ; @0x22EC 4a1b
	pshm   rea ; @0x22ED 4a1c
	pshm   bk ; @0x22EE 4a19
	stm    #0,rsa ; @0x22EF 771b
