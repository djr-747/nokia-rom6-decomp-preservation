; ROM6 0x3D3D ROUTINE_3D3D -- 60w, symbols.yaml data_word.
; Evidence: Bound 3D3D-3D78 (62w; exit RET FC00@3D78 byte-verified, exit scan clean; head F074 063A call idiom); entries 2x calld F274@DC/111->3D3D byte-verified (from 8210-setB block01 upload
; ORIGIN 0x3D3D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5aa
	stm    #31,brc
	rptb   0x3d77
	ld     *ar2,16,a
	add    *(0x571),16,a
	bitf   *(0x3eb5),#4
	bc     0x3d5b,ntc
	pshm   al
	pshm   ah
	pshm   ag
	ld     *(0x57a),16,a
	sub    *(0x578),16,a
	mpya   *ar4
	add    #16384,b
	stlm   b,t
	popm   ag
	popm   ah
	popm   al
	mpya   a
	sfta   a,2
	mpya   *ar0+
	sfta   b,2
	add    *ar5,16,b
	bitf   *(0x3eb5),#8
	bc     0x3d69,ntc
	ld     *(0x578),t
	ld     *(0x57a),16,a
	sfta   a,2
	maca   t,b
	ld     #1023,16,a
	min    a
	ldm    ar7,b
	cmpm   *(0x17),#2
	sub    #512,16,a
	xc     1,beq
	sth    a,*ar6-
	xc     1,tc
	sth    a,*ar1-
	xc     1,ntc
	sth    a,*ar1+
	ret
