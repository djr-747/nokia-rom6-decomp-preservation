; ROM6 0x4B67 FRAG_4B67 -- 26w, symbols.yaml data_word.
; Evidence: Bound 4B67-4B80 (26w; exit RET FC00@4B80 byte-verified, exit scan clean; STM-heavy straight-line immediates, zero calls/branches/refs — data-like texture FLAGGED); post-RET head (F
; ORIGIN 0x4B67
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #-11684,*ar3+
	st     #-26114,*ar3+
	st     #15445,*ar3+
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sfta   b,1
	stl    b,*ar3+
	sth    b,*ar3+
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sfta   b,1
	and    #31,16,b
	xor    #65280,16,b
	sth    b,*ar3+
	ld     #-1,b
	rpt    #3
	stl    b,*ar3+
	ret
