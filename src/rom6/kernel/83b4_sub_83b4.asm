; ROM6 0x83B4 SUB_83B4 -- 26w, symbols.yaml data_word.
; Evidence: Entry 4A17 7716 B194 F274 7F75 770E FFFF, prev FC00; zero callers; first exit ret @83CD len 26; interior calld 7F75 + call 7FC0 + calld 82FF/7FC6 + bc 83C6 cond; OVERLAP crosses ex
; Wave-12: exit ret @83CD owned here; ret-first twin 83cd_sub_83b4.asm deleted (was ret@83CD + dup of 83CE head).
; ORIGIN 0x83B4
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar7
	stm    #-20076,ar6
	calld  0x7f75
	stm    #-1,t
	ld     #0,a
	popm   al
	bc     0x83c6,aneq
	mar    *ar2+
	call   0x7fc0
	calld  0x82ff
	stm    #-8909,ar6
	calld  0x7fc6
	stm    #10884,ar2
	orm    #1024,*(0x2a87)
	ret
