; ROM6 0x8813 ROUTINE_8813 -- 14w, symbols.yaml data_word.
; Evidence: Bound 8813-8820 (8w; exit RET FC00@8820 byte-verified); entry call F074@8647->8813 byte-verified + post-RET head (FC00@8812 = retd of dark 87E9-8812 cell); preceded by dark gap 87E
; ORIGIN 0x8813
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	ld     #0,a
	stl    a,*(0x551)
	stl    a,*(0x550)
	rpt    #31
	mvmd   al,0x11ba
	rpt    #15
	mvmd   al,0x11da
	ret
