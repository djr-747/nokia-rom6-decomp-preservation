; ROM6 0x6458 MPYA_LADDER_6458 -- 69w, symbols.yaml data_word.
; Pool: stlm a,ah (8809, wave-12). STLM_SMEM_DIRECT has a catalog row (0x8800) and a leaf, but the leaf punts MMR-register routing downstream ("MMR-register routing is downstream") and no in-tree precedent routes an STLM into AH (accumulator-high as a page-0 MMR store of A-low -- effect ungrounded). Joint blockers: mpya b (F58C, MPYA_DST leaf exists but FRCT dark in-span, no ST1 setup) twice; SXM dark (no in-span setup, sign-extension assumptions unprovable). Otherwise groundable: bc/stl/cmpm/addm/xc/st/stm/ldu/and/ld/add/sub ladder with two mpya-accumulate lanes (T = 51 via stm, known) and tail calls 0x6871/0x688D (both C-bound: sub14_6871, dark 0x688D forward extern).
; Evidence: Fall-through entry from the 644A span (sub #51,a @6456-6457 abuts bc 0x6462,alt @6458); bc-alt lane rejoins; cmpm/addm/xc flag lane; dual ldu/and/stlm/mpya/add/add/sub lanes with xc 1,alt / xc 1,blt joins (XC-taken-runs, exact); second mpya lane on *(0x915) (add absolute, e54b shape); tail cmpm/and gate running C-bound SUB14_6871 (bc tc) then dark 0x688D via bneq/branch (F84C 676A + F074 688D); falls into the 649D span (stl b,*ar5 @649D abut). Bound 6458-649C.
; ORIGIN 0x6458
	.sect ".text"
	.mmregs
	.global _start
_start:
	bc     0x6462,alt
	stl    a,*ar3+
	cmpm   *ar3,#-12289
	addm   #1,*ar3
	xc     2,tc
	st     #0,*ar3
	stm    #12249,ar1
	ldu    *ar2-,a
	and    #3,a
	stlm   a,ah
	stm    #51,t
	mpya   b
	add    *ar6,b
	add    *ar2,b
	sub    #204,b,a
	stm    #2327,ar0
	xc     1,alt
	ld     b,a
	stl    a,*ar1+
	ld     *ar0,a
	add    *ar6,a
	sub    #102,a,b
	stm    #9487,ar0
	xc     1,blt
	ld     a,b
	stl    b,*ar1
	ldu    *(0x916),a
	and    #7,a
	stlm   a,ah
	stm    #51,t
	mpya   b
	add    *(0x915),b
	add    *ar6,b
	sub    #408,b,a
	stm    #12268,ar1
	xc     1,alt
	ld     b,a
	stl    a,*ar1
	ld     *ar0,a
	and    #240,a,b
	cmpm   *(0x8),#80
	bc     0x64a0,ntc
	call   0x6871
	bc     0x676a,bneq
	call   0x688d
