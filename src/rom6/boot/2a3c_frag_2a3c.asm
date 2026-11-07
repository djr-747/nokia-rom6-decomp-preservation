; ROM6 0x2A3C FRAG_2A3C -- 27w, symbols.yaml data_word.
; Evidence: Bound 2A3C-2A56 (27w; exit B F073@2A55->2A8A + operand 2A56, byte-verified; exit scan clean); entries 2x bc F820@2A1F/2A23->2A3C byte-verified (chained from FRAG_2A1C interior); ve
; ORIGIN 0x2A3C
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#64
	bc     0x2a57,ntc
	call   0x3ee1
	add    *(0x3ee7),a
	sub    *(0x36a),a,b
	st     #128,*ar3
	stm    #4724,ar3
	stm    #4718,ar2
	xc     1,bgt
	ld     b,a
	dld    *(0x3ef8),b
	dst    b,*ar3
	st     #256,*ar2+
	stl    a,*ar2-
	b      0x2a8a
