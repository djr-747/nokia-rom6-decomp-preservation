; ROM6 0x84CF SUB_84CF -- 50w, symbols.yaml data_word.
; Evidence: Entry F074 0648 61F8 058F 000F FC30, prev FC00; zero F074/F274 callers (cc-forms only); first exit ret @8500 len 50; interior call 0648 + calld 2262, branch-free; HYPOTHESIS.
; Wave-12: exit ret @8500 owned here. Deleted twins: 84ce (ret@84CE + 84CF-head dup; ret owned by 84af), 8500 (ret@8500 + dup of 8501 through 8529-head), 84ae giant (84AE by 8449; 84AF-84CE by 84af; 84CF-8500 here; 8501-8507 by 8501; 8508-8528 by new lane spans 8508/8513/851E; 8529+ by 8529).
; ORIGIN 0x84CF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x648
	bitf   *(0x58f),#15
	rc     tc
	andm   #-105,*(0x537)
	calld  0x2262
	stm    #9,ar2
	st     #0,*(0x4fb)
	stm    #528,ar1
	ld     #1,a
	mvmd   ar1,0x554
	rpt    #7
	stl    a,*ar1+
	ld     #0,a
	stl    a,*(0x556)
	stl    a,*(0x558)
	stm    #544,ar1
	mvmd   ar1,0x555
	rpt    #7
	stl    a,*ar1+
	andm   #-17,*(0x552)
	orm    #1024,*(0x552)
	st     #12,*(0x540)
	mpy    *(0x3eae),#3,a
	sfta   a,-2
	stl    a,*(0x541)
	ret
