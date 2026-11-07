; ROM6 0xE492 BLK_E492 -- 57w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E4CA (57w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE492
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,0x62
	pshm   ar4
	pshm   ar5
	pshm   ar3
	pshm   ar1
	mvmm   ar5,ar4
	stm    #9,brc
	rptbd  0xe4a0
	stm    #-1,t
	ld     *ar2+,ts,a
	add    *ar3+,ts,a
	stl    a,*ar4+
	calld  0xe4dd
	mvmm   ar1,ar3
	mvmm   ar5,ar2
	popm   ar3
	popm   ar2
	ld     0x62,a
	pshm   ar2
	pshm   ar3
	ccd    0xe4dd,aneq
	mar    *+ar3(0xb)
	stm    #9,brc
	popm   ar3
	popm   ar1
	popm   ar2
	popm   ar4
	stm    #-1,t
	rptbd  0xe4bc
	pshm   ar4
	pshm   ar2
	ld     *ar1+,ts,a
	add    *ar4+,ts,a
	stl    a,*ar2+
	popm   ar2
	pshm   ar3
	calld  0xe4dd
	mar    *+ar3(0x16)
	popm   ar3
	popm   ar2
	ld     0x62,a
	ccd    0xe4dd,aneq
	mar    *+ar3(0x21)
	ret
