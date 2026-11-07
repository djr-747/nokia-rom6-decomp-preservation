; ROM6 0x4DA7 DISPATCH_4DA7 -- 51w, symbols.yaml data_word.
; Evidence: Bound 4DA7-4DD9 (exit BACCD F6E2@4DD7 + delays 4DD8/4DD9 byte-verified; 1w shorter than critic 4DDA — catalog BACCD is 1-word op + 2 delays); callers 3x F274 @4BE5/4C51/4CFE (gap-i
; ORIGIN 0x4DA7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	pshm   al
	sftl   a,-1
	add    #-20220,a
	stlm   a,ar1
	mvdm   0x264a,ar3
	ld     *ar1,a
	cmpm   *(0x250f),#34
	bc     0x4dd7,ntc
	cmpm   *(0x34bf),#0
	bc     0x4dd7,tc
	bitf   *(0x3490),#2
	bc     0x4dd7,tc
	cmpm   *(0x34bf),#4
	ld     *(0x264a),b
	xc     2,tc
	sub    #14304,b
	xc     2,ntc
	sub    #15072,b
	bitf   *(0x3490),#1
	nop
	nop
	xc     2,tc
	add    #15072,b
	xc     2,ntc
	add    #9312,b
	stlm   b,ar3
	baccd  a
	stm    #8,ar1
