; ROM6 0xE837 BLK_E837 -- 30w, symbols.yaml data_word.
; Evidence: Post-RET head; EXIT CORRECTED by all-paths walk: sole exit fbacc F5E6 @E854 (true end E854, span 30 not 173); straight-line, no interior branches; E855+ is a separate post-fbacc he
; ORIGIN 0xE837
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar3
	stm    #15854,ar3
	stm    #15878,ar4
	ld     #0,b
	sub    *ar3+,*ar4+,a
	rpt    #22
	sqdst  *ar3+,*ar4+
	sqdst  *ar3,*ar4
	mvkd   0x3e20,*(0x3e22)
	sfta   b,5
	sth    b,*(0x3e20)
	ld     *(0x3e23),16,a
	min    a
	sth    a,*(0x3e23)
	ld     *(0x3e21),16,a
	add    b,a
	sth    a,*(0x3e21)
	popm   ar3
	popm   bh
	popm   bl
	fbacc  b
