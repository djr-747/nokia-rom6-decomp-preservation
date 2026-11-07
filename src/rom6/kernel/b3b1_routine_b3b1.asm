; ROM6 0xB3B1 ROUTINE_B3B1 -- 49w, symbols.yaml data_word.
; Evidence: Bound B3B1-B3E1 (81w; exit RET FC00@B3E1 byte-verified; interior joins B@B3C5->B3D1 + B@B3CD->B3D1 in-span; exit scan otherwise clean); entries 6x call F074@B1A8/B1CD/B1E3/B1FC/B20
; ORIGIN 0xB3B1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a8
	stm    #-19120,ar5
	stm    #-19099,ar6
	ld     #-19108,a
	call   0xaeec
	call   0xaf40
	ld     *(0x3490),a
	and    #7,a,b
	bc     0xb3c7,bneq
	stm    #13508,ar2
	b      0xb3d1
	and    #1,a,b
	bc     0xb3cf,beq
	stm    #13509,ar2
	b      0xb3d1
	stm    #13510,ar2
	pshm   ar2
	mvdk   *ar2,0x262d
	call   0xa654
	popm   ar2
	stm    #-19120,ar3
	stm    #-19099,ar6
	ld     #-19108,a
	mvkd   0x262d,*ar2
	call   0xaf16
	ret
