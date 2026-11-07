; ROM6 0xA5E1 MEAS_SETUP_A -- 17w, symbols.yaml data_word.
; Evidence: Entry F074 065A 61F8 2628 0200 FC20; first-RET @0xA5F1 (len 17); 5 callers AFD7 B032 B03E B0AB B34F; body calls 0x65A/0x3D79; distinct 0x65A primitive vs 0x656/0x658 message group;
; ORIGIN 0xA5E1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65a
	bitf   *(0x2628),#512
	rc     ntc
	ld     #12,a
	ld     *(0x2613),b
	calld  0x3d79
	stm    #1843,ar1
	st     #1,*(0x22a)
	ret
