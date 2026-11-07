; ROM6 0x9414 MEAS_DISPATCH_9414 -- 26w, symbols.yaml data_word.
; Evidence: Branch-reached from 0x93CE cluster (F820 @0x93D3/0x93D9/0x93E1, F073 @0x940E); calls 0x99A4/0x9A11/0x96BD; RET FC00 @0x942D. Bound 9414-942D (wave-5: exit + post-RET byte-verified;
; ORIGIN 0x9414
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #8447,ar4
	mvdm   0x21fc,ar3
	stm    #250,bk
	bitf   *ar4,#1024
	rc     tc
	bitf   *ar4,#512
	bc     0x9429,tc
	bitf   *ar4,#256
	bc     0x9429,tc
	call   0x99a4
	b      0x942b
	call   0x9a11
	call   0x96bd
	ret
