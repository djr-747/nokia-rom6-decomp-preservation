; ROM6 0xDC2E SUB_DC2E -- 19w, symbols.yaml data_word.
; Evidence: Entry 771A 009F 7713 0008; first exit retd FE00 @DC40; Bound DC41-DC42 (RETD@DC40 delay slots — wave-11 spill fix); caller F274 @DFE6 verified; HYPOTHESIS.
; ORIGIN 0xDC2E
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #159,brc
	stm    #8,ar3
	ld     #0,b
	rptbd  0xdc38
	stm    #19,ar2
	sub    *ar2,*ar4+,a
	or     a,b
	ld     *(0xc4c),a
	and    #-3,a
	xc     2,beq
	or     #2,a
	retd
