; ROM6 0x4557 FRAG_4557 -- 16w, symbols.yaml data_word.
; Evidence: Bound 4557-4566 (16w; exit RET FC00@4566 byte-verified, exit scan clean); post-RET head (FC00@4556 = SUB_454F exit, CODE); interior out-call F074@4563->052A (code signature — overt
; Wave-13: lane @4567-4569 annexed (gap orphan; portr pa13 + ret).
; ORIGIN 0x4557
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     0x6a,16,b
	ld     0x6a,16,b
	ld     0x5c,16,b
	ld     0x5c,16,b
	ld     0x78,16,b
	ldm    ar3,b
	stm    #1322,ar7
	rpt    #2
	mvpd   0x4567,*ar7+
	stl    b,*(0x52b)
	call   0x52a
	ret
	portr  13,*ar4+
	ret
