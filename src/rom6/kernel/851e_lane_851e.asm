; ROM6 0x851E LANE_851E -- 11w (overlap-split wave-12).
; Evidence: Bound 851E-8528 (stm/stm/call 8611/stm/call 853B/ret @8528); zero F074/F274 callers; shape-twin of the 8508 lane (AR2 preset + 853B tail differ); covered only by the deleted 8500-giant before. C intent in 851e_lane_851e.c. Recombine-clean.
; ORIGIN 0x851E
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-18615,ar2
	stm    #12508,ar5
	call   0x8611
	stm    #-18579,ar6
	call   0x853b
	ret
