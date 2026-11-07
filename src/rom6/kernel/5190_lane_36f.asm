; ROM6 0x5190 LANE_36F -- 60w, symbols.yaml data_word.
; Evidence: Bound 5190-51CB (60w; no own RET: hit falls to HIT_51CC@51CC, miss B@51AB->51D4, scan misses bc F845@5192/51A1/51A7->51AD; 51C8 miss bc F845->51D4 else falls 51CC); entry ld *(0x36f) (10F8 036F); exterior entry bc F845@518A->5190 from ROUTINE_516A span.
; ORIGIN 0x5190
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x36f),a
	bc     0x51ad,aeq
	stlm   a,ar1
	stm    #880,ar2
	ld     *(0x2f62),b
	and    #255,b
	mar    *ar1-
	ld     *ar2,-8,a
	and    #255,a
	sub    b,a
	bc     0x51ad,aeq
	ld     *ar2+,a
	and    #255,a
	sub    b,a
	bc     0x51ad,aeq
	banz   0x519c,*ar1-
	b      0x51d4
	ld     *(0x375),a
	bc     0x51cc,aeq
	stlm   a,ar1
	stm    #886,ar2
	ld     *(0x2f61),8,b
	and    #-256,b
	ld     *(0x2f62),-8,a
	and    #255,a
	mar    *ar1-
	add    a,b
	and    #-1,b
	ldu    *ar2+,a
	sub    b,a
	bc     0x51d0,aeq
	banz   0x51c2,*ar1-
	ld     *(0x374),a
	bc     0x51d4,aeq
