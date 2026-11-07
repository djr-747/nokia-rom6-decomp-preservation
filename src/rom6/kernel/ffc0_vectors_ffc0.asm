; ROM6 0xFFC0 VECTORS_FFC0 -- 64w, symbols.yaml data_word.
; Evidence: Bound FFC0-FFFF (64w vectors + pad); 4-word BD slots 4A1E 4A06 F880 <addr> (byte-verified FFC0 slot: F880 22DA): FFC0->0x22DA SAMPLE_ISR, FFC4/C8/E0->0x27CD FRAME_ISR, FFE4->0x2B53
; ORIGIN 0xFFC0
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @FFC0 4a1e pshm   xpc
	pshm   xpc
	; @FFC1 4a06 pshm   st0
	pshm   st0
	; @FFC2 f880 fb     0x22da
	fb     0x22da
	; @FFC4 4a1e pshm   xpc
	pshm   xpc
	; @FFC5 4a06 pshm   st0
	pshm   st0
	; @FFC6 f880 fb     0x27cd
	fb     0x27cd
	; @FFC8 4a1e pshm   xpc
	pshm   xpc
	; @FFC9 4a06 pshm   st0
	pshm   st0
	; @FFCA f880 fb     0x27cd
	fb     0x27cd
	; @FFCC 4a1e pshm   xpc
	pshm   xpc
	; @FFCD f880 fb     0x5fa
	fb     0x5fa
	; @FFCF f495 nop
	nop
	; @FFD0 4a1e pshm   xpc
	pshm   xpc
	; @FFD1 4a06 pshm   st0
	pshm   st0
	; @FFD2 f880 fb     0x25df
	fb     0x25df
	; @FFD4 f49b retf
	retf
	; @FFD5 f495 nop
	nop
	; @FFD6 f495 nop
	nop
	; @FFD7 f495 nop
	nop
	; @FFD8 f49b retf
	retf
	; @FFD9 f495 nop
	nop
	; @FFDA f495 nop
	nop
	; @FFDB f495 nop
	nop
	; @FFDC f49b retf
	retf
	; @FFDD f495 nop
	nop
	; @FFDE f495 nop
	nop
	; @FFDF f495 nop
	nop
	; @FFE0 4a1e pshm   xpc
	pshm   xpc
	; @FFE1 4a06 pshm   st0
	pshm   st0
	; @FFE2 f880 fb     0x27cd
	fb     0x27cd
	; @FFE4 4a1e pshm   xpc
	pshm   xpc
	; @FFE5 4a06 pshm   st0
	pshm   st0
	; @FFE6 f880 fb     0x2b53
	fb     0x2b53
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
	.word 0x0000 ; zero fill
