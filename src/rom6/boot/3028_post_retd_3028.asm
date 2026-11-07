; ROM6 0x3028 POST_RETD_3028 -- 23w, symbols.yaml data_word.
; Evidence: Entry E800 (ld #0,a) at post-retd boundary (FE00@3025 + delay 80F8/2648 @3026/3027); bound 3028-303E (23w, exit F073@303D->0x2000 + operand 303E); callers 2x ext F073->3028 @452A/4
; ORIGIN 0x3028
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	call   0x3986
	andm   #-2049,*(0x552)
	stm    #705,sp
	stl    a,*(0x54f)
	call   0x2e2f
	ld     *(0x871),a
	sub    #0,a,b
	bc     0x303d,beq
	stlm   a,ar2
	call   0x226c
	b      0x2000
