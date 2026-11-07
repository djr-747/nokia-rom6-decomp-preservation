; ROM6 0x8854 HEAD_8854 -- 64w, symbols.yaml data_word.
; Evidence: Entry 7714 09C8 F274 86FB; bound 8854-8893 (exit F073@8892->889B); fall-through after F4E2 bacc end of TABLE_ENGINE_8821 (ends 8853, no overlap); interior calld 86FB@8856; join F84
; ORIGIN 0x8854
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2504,ar4
	calld  0x86fb
	stm    #12432,ar3
	stm    #1310,ar4
	andm   #-7,*ar4
	stm    #1370,ar2
	ld     *ar2,a
	ld     *ar4,b
	and    #1,b
	add    a,b
	bc     0x888d,beq
	cmpm   *(0xb),#1
	sub    #1,b
	xc     2,tc
	andm   #-2,*ar4
	xc     2,ntc
	sub    #1,a
	stl    a,*ar2
	bitf   *(0x577),#-32768
	add    #1284,b
	stlm   b,ar2
	stm    #12090,ar3
	ld     *ar2,a
	xc     1,ntc
	ld     #64,a
	stl    a,*ar5
	stm    #12443,ar2
	stm    #3,brc
	rptbd  0x888c
	stm    #17,ar0
	add    *ar3+,a,b
	ld     *ar2,a
	min    b
	ld     *ar5,a
	stl    b,*ar2+0
	stm    #4491,ar4
	rpt    #16
	mvkd   0x9c8,*ar4+
	b      0x889b
