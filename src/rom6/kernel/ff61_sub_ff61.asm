; ROM6 0xFF61 SUB_FF61 -- 8w, symbols.yaml data_word.
; Evidence: Entry E724 (interior call-entry of RUN_FF40); bound FF61-FF68 (exit FC00@FF68); 3x F074 callers @FF6D/71/75 objdump-verified; HYPOTHESIS.
; ORIGIN 0xFF61
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @FF61 e724 mvmm   ar2,ar4
	mvmm   ar2,ar4
	; @FF62 4719 rpt    0x19
	rpt    0x19
	; @FF63 e518 mvdd   *ar3,*ar2+
	mvdd   *ar3,*ar2+
	; @FF64 e742 mvmm   ar4,ar2
	mvmm   ar4,ar2
	; @FF65 4719 rpt    0x19
	rpt    0x19
	; @FF66 e318 abdst  *ar3,*ar2+
	abdst  *ar3,*ar2+
	; @FF67 e742 mvmm   ar4,ar2
	mvmm   ar4,ar2
	; @FF68 fc00 ret
	ret
