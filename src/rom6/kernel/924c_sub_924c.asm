; ROM6 0x924C SUB_924C -- 28w, symbols.yaml data_word.
; Evidence: Bound 924C-9267 (28w; exit RET FC00@9267); entry F074 0594; caller F274 calld@0x4D02 byte-verified; interior calls 9217/9042/9315 (existing); F0EC tail prefix falls through; HYPOTH
; ORIGIN 0x924C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x9217
	ld     #127,a
	rpt    #7
	mvmd   al,0x3224
	stm    #227,brc
	call   0x9042
	stm    #12836,ar7
	stm    #3,brc
	call   0x9042
	stm    #227,brc
	call   0x9315
	sftl   a,12
	stl    a,*ar3
	rpt    #14
	mvdk   *ar3+,0x2f80
	ret
