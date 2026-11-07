; ROM6 0x4B9A FRAG_4B9A -- 14w, symbols.yaml data_word.
; Evidence: Bound 4B9A-4BA7 (14w; exit RET FC00@4BA7 byte-verified, exit scan clean); entries bc F845@4B86/ 4B8A->4B9A byte-verified (exterior, existing 4B81 span) + B F073@4B98->4BA6 mid-span
; ORIGIN 0x4B9A
	.sect ".text"
	.mmregs
	.global _start
_start:
	andm   #8191,*ar2+
	stm    #9,brc
	rptb   0x4ba5
	ld     *ar2-,13,a
	or     *ar2,a
	stl    a,*ar2+
	ld     *ar2,-3,a
	stl    a,*ar2+
	ssbx   st1,sxm
	ret
