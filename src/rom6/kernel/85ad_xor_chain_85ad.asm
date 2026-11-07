; ROM6 0x85AD XOR_CHAIN_85AD -- 55w, symbols.yaml data_word.
; Evidence: Entry 7192 0013 1293 F0C8 1C83 138B; first exit ret FC00 @85E3 (55 words mvdk/ldu/xor chain); callers F074 @8596/85A0/85AA verified; HYPOTHESIS.
; ORIGIN 0x85AD
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdk   *ar2+,0x13
	ldu    *ar3+,a
	xor    a,8
	xor    *ar3,a
	ldu    *ar3-,b
	xor    b,8
	xor    *ar3,b
	and    #-1,b
	sftl   b,8
	or     b,-16
	xor    *ar3,b
	and    #-1,b
	sftl   b,8
	or     b,-16
	mvdk   *ar2+,0x13
	xor    *ar3+,b
	xor    *ar3,a
	sftl   a,8
	xor    *ar3-,a
	sftl   a,-8
	mvdk   *ar2+,0x13
	xor    *ar3,b
	sftl   b,8
	xor    *ar3+,b
	sftl   b,-8
	and    #-1,b
	sftl   b,8
	or     b,-16
	xor    *ar3,b
	and    #-1,b
	sftl   b,8
	or     b,-16
	xor    *ar3-,a
	and    #-1,a
	sftl   a,8
	or     a,-16
	xor    *ar3+,a
	xor    *ar3,a
	and    #-1,a
	sftl   a,8
	or     a,-16
	mvdk   *ar2,0x13
	stl    a,*ar3+
	stl    b,*ar3
	ret
