; ROM6 0xE46B SUB39_E46B -- 39w (overlap-split wave-12).
; Evidence: Pool: rptbd/banzd delayed forms + stlm have no direct C form (deferred execution, flagged); interior rptbd E48A + banzd E47A, no inner calls. Bound E46B-E491 (entry ld #0,a; stm/stm/ld/st/st/mvmm/sub/st/ldm/stlm/mar/rptbd-block/banzd/dst/add/ret @E491). Callers F274 @E4DF/E4E4 (per prior e491 header, retained). Carved from e46a twin (its header described e442; deleted) + supersedes mis-origin e491 file (deleted; its 39 bytes were ret@E491 + e492-head). Recombine-clean.
; ORIGIN 0xE46B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	stm    #-4,ar0
	stm    #3,ar1
	stlm   a,ar5
	st     #1,0x64
	st     #256,*ar3+
	stl    a,*ar3+
	mvmm   ar3,ar7
	sub    *ar2+,10,a
	st     a,*ar3+ || ld     *ar2+,t
	stl    a,*ar3+
	mvmm   ar3,ar4
	ldm    ar5,a
	stlm   a,brc
	mar    *ar4+0%
	rptbd  0xe48a
	mvdd   *ar4+,*ar3+
	mvdd   *ar4+,*ar3+
	mpy    *ar2,*ar4+,b
	ldu    *ar4+,a
	sfta   a,15
	mpya   a
	maca   0x64,b
	dld    *ar4+0%,a
	dadd   *ar4-0%,a
	sub    b,1,a
	dst    a,*ar4+0%
	dld    *ar7,a
	sub    *ar2+,10,a
	banzd  0xe47a,*ar1-
	dst    a,*ar7
	add    *ar5+,*ar2+,a
	ret
