; ROM6 0x956E FRAG_956E -- 35w, symbols.yaml data_word.
; Evidence: Bound 956E-9590 (exit F073@958F->95A2); entry F844@9559 (objdump bc->956E); interior bc@9575->9591, bcd@957E->958B, bc@958D->959D; micro bd-tail 9591-95A1 folded in note, no symbol
; ORIGIN 0x956E
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *(0x20fa),b
	sub    #2,b
	st     #0,*(0x20fa)
	bc     0x9591,blt
	ld     #0,a
	ld     *(0x21fa),b
	stl    b,*(0x21fb)
	bitf   *ar2,#128
	bcd    0x958b,tc
	stl    a,*(0x20fd)
	bitf   *(0x20ff),#64
	ldm    ar3,b
	sftl   b,8
	xc     1,tc
	stlm   b,ar3
	xc     1,ntc
	ld     #2,a
	bitf   *ar2,#1536
	bc     0x959d,tc
	b      0x95a2
