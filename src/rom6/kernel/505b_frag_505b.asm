; ROM6 0x505B FRAG_505B -- 87w, symbols.yaml data_word.
; Evidence: Bound 505B-50B1 (exit FE00@50AF + delays 50B0/50B1, abuts existing FEEDER_2F61_50B2); post-ret abut, zero callers and zero interior calls; straight-line flag-pack math tail; HYPOTH
; ORIGIN 0x505B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+,a
	and    #32767,a
	ld     *ar2+,b
	and    #-8,b
	mvdk   *ar2,0xc
	andm   #3,*(0xc)
	sftl   b,12
	or     b,a
	stl    a,*ar3+
	sfta   a,-16
	ld     *ar2+,b
	and    #-64,b
	mvdk   *ar2,0xc
	andm   #31,*(0xc)
	sftl   b,8
	or     b,a
	stl    a,*ar3+
	sftl   a,-16
	ld     *ar2+,b
	and    #-512,b
	mvdk   *ar2,0xc
	andm   #255,*(0xc)
	sftl   b,4
	or     b,a
	stl    a,*ar3+
	sftl   a,-16
	ld     *ar2+,b
	and    #-4096,b
	mvdk   *ar2,0xc
	andm   #2047,*(0xc)
	or     b,a
	stl    a,*ar3+
	sftl   a,-16
	ld     *ar2+,b
	and    #-32768,b
	mvdk   *ar2+,0xc
	andm   #16383,*(0xc)
	sftl   b,-4
	or     b,a
	stl    a,*ar3+
	sftl   a,-16
	ld     *ar2+,b
	and    #-4,b
	mvdk   *ar2,0xc
	andm   #1,*(0xc)
	sftl   b,8
	or     b,a
	stl    a,*ar3+
	sftl   a,-16
	ld     *ar2+,b
	and    #-32,b
	mvdk   *ar2,0xc
	andm   #15,*(0xc)
	sftl   b,4
	or     b,a
	retd
	stl    a,*ar3+
	sth    a,*ar3+
