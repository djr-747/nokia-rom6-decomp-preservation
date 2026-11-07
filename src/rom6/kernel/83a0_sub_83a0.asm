; ROM6 0x83A0 SUB_83A0 -- 20w, symbols.yaml data_word.
; Evidence: Entry 7716 B18C F274 7F55 770E FFFE, prev FC00; zero F074/F274 callers full-image; first exit ret @83B3 len 20 entry-linear; interior calld 7F55/7F95/7FC6 chain; gap-followup verif
; Wave-12: exit ret @83B3 owned here; ret-first twin 83b3_sub_83a0.asm deleted (was ret@83B3 + dup of 83B4 head).
; ORIGIN 0x83A0
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-20084,ar6
	calld  0x7f55
	stm    #-2,t
	stm    #-20116,ar6
	calld  0x7f95
	stm    #-6,t
	calld  0x7fc6
	stm    #10884,ar2
	orm    #1536,*(0x2a87)
	ret
