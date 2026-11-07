; ROM6 0x2867 FRAG_2867 -- 14w, symbols.yaml data_word.
; Evidence: Bound 2867-2874 (8w + operand; exit F073@2873->283D + operand 2874); post-FRETE entry (FRETE@2866 closes STRETCH_2800); bc-entry F84C@2823; words 69F8/0866/0001 (orm 0x866) + pa2 p
; ORIGIN 0x2867
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #1,*(0x866)
	portr  2,*(0x8)
	or     #2,a
	nop
	portw  *(0x8),2
	b      0x283d
