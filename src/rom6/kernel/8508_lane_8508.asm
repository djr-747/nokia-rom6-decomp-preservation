; ROM6 0x8508 LANE_8508 -- 11w (overlap-split wave-12).
; Evidence: Bound 8508-8512 (stm/stm/call 8611/stm/call 8555/ret @8512); zero F074/F274 callers (lane entered by fall-through/abut, unconfirmed); carved from deleted 8500-giant + deleted 8507 ret-twin (which held the 8508-850D head). C intent in 8507_sub_8501.c (head) -- full-lane intent below in spirit; recombine vehicle for words 8508-8512. Recombine-clean.
; ORIGIN 0x8508
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-18609,ar2
	stm    #12508,ar5
	call   0x8611
	stm    #-18591,ar6
	call   0x8555
	ret
