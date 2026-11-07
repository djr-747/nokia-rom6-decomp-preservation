; ROM6 0x99E6 ROUTINE_99E6 -- 25w, symbols.yaml data_word.
; Evidence: Bound 99E6-99FE (25w; exit RETD FE00@99FC + delays 99FD-99FE (stl 2w), byte-verified; exit scan clean); entry call F074@9446->99E6 byte-verified (exterior from COBBA_VERIFY_LOOP [9
; ORIGIN 0x99E6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ce
	mvmm   ar2,ar1
	mar    *ar2+%
	mar    *ar2+%
	ld     *ar2+%,b
	add    #7,b
	sfta   b,-1
	mvmm   ar1,ar2
	ld     #0,a
	rpt    *(0xb)
	xor    *ar2+%,a
	bcd    0x99ff,aeq
	mvmd   ar2,0x21fb
	st     #1,*(0x21fe)
	ld     #0,a
	retd
	stl    a,*(0x20fe)
