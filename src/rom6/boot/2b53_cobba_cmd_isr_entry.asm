; ROM6 0x2B53 COBBA_CMD_ISR_ENTRY -- 1w, symbols.yaml program_word.
; Evidence: V25 HPI-word request ISR. Gates on *(0x870) (HPI word 0x70, MCU 0x100E0 Cobba slot) and *(0x4C2)<4. CALL 0xB4F8, clears the word, FRETE.
; Pool: 1-word head (pshm st1); continuation 0x2B54 unowned -- boundary open past this word, revisit in the overlap pass. stays .asm, bytes verified.
; ORIGIN 0x2B53
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   st1
