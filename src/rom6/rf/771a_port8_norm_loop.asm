; ROM6 0x771A PORT8_NORM_LOOP -- 21w, symbols.yaml data_word.
; Evidence: Entry ld *(2F06); bound 771A-772E; callers 760B/764C/7668 (in 7522); reada *(0x8)@771E + norm loop + call 7967 + banzd self-loop; HYPOTHESIS.
; ORIGIN 0x771A
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x2f06),a
	and    #-1,a
	reada  *(0x8)
	mvmd   al,0x9
	norm   a
	addm   #-1,*(0xe)
	call   0x7967
	mvdd   *ar4+,*ar2+
	mvdd   *ar4-,*ar2+
	banzd  0x771a,*ar7-
	mar    *+ar3(0xffe0)
	ret
