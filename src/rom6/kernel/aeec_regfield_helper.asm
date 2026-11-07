; ROM6 0xAEEC REGFIELD_HELPER -- 40w, symbols.yaml data_word.
; Evidence: Entry 11F8 3490 ld *(0x3490),b; F330 0007 and #7; 81F8 0013 stl *(0x13) + rptb loop; zero F074/F274 in body; first-RET @0xAF13 (len 40); 3 callers B3A4 B3B9 B422; HYPOTHESIS regfie
; ORIGIN 0xAEEC
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x3490),b
	and    #7,b
	stl    b,*(0x13)
	add    *(0x13),a
	stl    a,*(0x13)
	ld     *ar5+,b
	sub    #2,b
	stl    b,*(0x1a)
	mvdk   *ar3,0x12
	rptb   0xaf12
	mvdk   *ar5+,0x14
	ld     *ar6,a
	sub    #1,a
	bc     0xaf13,alt
	bc     0xaf0f,aeq
	stl    a,*(0x11)
	rpt    *(0x11)
	mvdd   *ar2+,*ar4+
	b      0xaf10
	mvdd   *ar2+,*ar4
	mar    *ar6+
	nop
	nop
	ret
