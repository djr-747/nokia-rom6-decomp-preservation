; ROM6 0x83CE SUB_83CE -- 26w, symbols.yaml data_word.
; Evidence: Entry 4A17 7716 B163 F274 7F75 770E 0000, prev FC00; zero callers; first exit ret @83E7 len 26; interior calld 7F75 + call 7FC0 + calld 82FF/7FC6 + bc 83E0 cond; OVERLAP crosses ex
; Wave-12: exit ret @83E7 owned here; ret-first twin 83e7_sub_83ce.asm deleted (was ret@83E7 + dup of 83E8-8400).
; ORIGIN 0x83CE
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar7
	stm    #-20125,ar6
	calld  0x7f75
	stm    #0,t
	ld     #0,a
	popm   al
	bc     0x83e0,aneq
	mar    *ar2+
	call   0x7fc0
	calld  0x82ff
	stm    #-8966,ar6
	calld  0x7fc6
	stm    #10884,ar2
	orm    #1024,*(0x2a87)
	ret
