; ROM6 0x372E FRAG_372E -- 37w, symbols.yaml data_word.
; Evidence: Bound 372E-3752 (37w incl operand; exit B F073@3751->2E64 match loop); entry bc F820@3700->372E (opcode-verified); head 60F8 0008 0006 F820 3753; interior CALL 2E2F/E79D/E80C/2C88;
; ORIGIN 0x372E
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#6
	bc     0x3753,ntc
	mvdk   *ar2+%,0x27fe
	mvdk   *ar2+%,0x27ff
	mvdk   *ar2+%,0x2940
	mvdk   *ar2+%,0x2941
	mvdk   *ar2+%,0x2979
	mvdk   *ar2+%,0x244f
	mvdk   *ar2+%,0x2450
	call   0x2e2f
	call   0xe79d
	call   0xe80c
	stm    #10217,ar3
	stm    #158,ar4
	stm    #2,ar5
	st     #8,*ar3
	call   0x2c88
	b      0x2e64
