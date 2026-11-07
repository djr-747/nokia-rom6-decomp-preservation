; ROM6 0x8501 SUB_8501 -- 7w, symbols.yaml data_word.
; Evidence: Entry 7715 B75B 7716 B76D F074 853B, prev FC00; zero callers; first exit ret @8507 len 7; interior call 853B; HYPOTHESIS.
; Wave-12: exit ret @8507 owned here; ret-first twin 8507_sub_8501.asm deleted (was ret@8507 + dup of 8508-850D head, now 8508_lane_8508.asm).
; ORIGIN 0x8501
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @8501 7715 stm    #-18597,ar5
	stm    #-18597,ar5
	; @8503 7716 stm    #-18579,ar6
	stm    #-18579,ar6
	; @8505 f074 call   0x853b
	call   0x853b
	; @8507 fc00 ret
	ret
