; ROM6 0x7D31 SUB_7D31 -- 47w, symbols.yaml data_word.
; Evidence: Entry 76F8 058C 0004 E800 80F8 264F; zero callers (bc @7C6A NOT counted); conditionals only (rc ntc @7D56 passed per ret/retd-only exit rule -- convention accepted, not independent
; ORIGIN 0x7D31
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #4,*(0x58c)
	ld     #0,a
	stl    a,*(0x264f)
	stl    a,*(0x2650)
	stl    a,*(0x2631)
	andm   #4015,*(0x2639)
	ld     *ar2,b
	and    #240,b
	cmpm   *(0xb),#192
	bc     0x7d48,tc
	stl    a,*(0x2579)
	stl    a,*(0x259f)
	stl    a,*(0x25a0)
	stl    a,*(0x25c1)
	cmpm   *(0x2510),#192
	bc     0x7d57,tc
	cmpm   *(0x2510),#177
	rc     ntc
	stl    a,*(0x2630)
	st     #-1,*(0x264f)
	andm   #319,*(0x2ef9)
	ret
