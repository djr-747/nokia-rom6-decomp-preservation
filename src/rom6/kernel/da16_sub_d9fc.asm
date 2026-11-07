; ROM6 0xDA16 SUB_D9FC -- 2w, symbols.yaml data_word.
; Evidence: Entry 7712 0A5E E807 8092; first exit retd FE00 @DA15 entry-linear; Bound DA16-DA17 (RETD@DA15 delay slots — wave-11 spill fix); caller F274 @D9BF verified; HYPOTHESIS.
; ORIGIN 0xDA16
	.sect ".text"
	.mmregs
	.global _start
_start:
	rpt    #27
	sth    a,*ar2+
