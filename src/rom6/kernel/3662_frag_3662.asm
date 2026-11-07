; ROM6 0x3662 FRAG_3662 -- 18w, symbols.yaml data_word.
; Evidence: Bound 3662-3673 (18w, exit FC00@3673); entry bc F830@365C (taken-path); post-B head (FRAG_3640 exit F073@3660->3664 adjacent); head F340 0100 8184 4815 8090 6183 0001 FC20 6183 000
; ORIGIN 0x3662
	.sect ".text"
	.mmregs
	.global _start
_start:
	or     #256,b
	stl    b,*ar4
	ldm    ar5,a
	stl    a,*ar0+
	bitf   *ar3,#1
	rc     ntc
	bitf   *ar3,#8
	bc     0x3671,ntc
	orm    #512,*(0x54f)
	ldm    ar6,a
	stl    a,*ar0
	ret
