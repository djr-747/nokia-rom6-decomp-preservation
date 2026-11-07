; ROM6 0x8513 LANE_8513 -- 11w (overlap-split wave-12).
; Evidence: Bound 8513-851D (stm/stm/call 8611/stm/call 8555/ret @851D); zero F074/F274 callers; shape-twin of the 8508 lane (AR2 preset differs); covered only by the deleted 8500-giant before. C intent in 8513_lane_8513.c. Recombine-clean.
; ORIGIN 0x8513
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-18603,ar2
	stm    #12508,ar5
	call   0x8611
	stm    #-18591,ar6
	call   0x8555
	ret
