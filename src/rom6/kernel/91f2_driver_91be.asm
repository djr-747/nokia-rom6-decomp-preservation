; ROM6 0x91F2 DRIVER_91BE -- 37w (overlap-trimmed, wave-12).
; Evidence: Entry F074 0594 E864 EC03 mvmd; dual rptb streams + calls 0x918C/0x9004; RET @91F2 len 53; 1x F074 @751F; HYPOTHESIS driver (AR6 0x80 variant vs 0x91F3 0x160). Words 9217-9226 duplicated the head of the 9217 span (owned by 9217_late_leaf_9217.asm); trimmed so one .asm owns every word (span now 91F2-9216, ends with E3's ret).
; Wave-12: exit ret @9216 owned here; ret-wrapper span 9216_driver_91f3 (.asm + .c) deleted (was duplicate ret word).
; ORIGIN 0x91F2
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
	call   0x594
	ld     #100,a
	rpt    #3
	mvmd   al,0x3032
	stm    #352,ar6
	stm    #12196,ar7
	stm    #145,brc
	rptb   0x9203
	ld     *ar7+,-6,a
	stl    a,*ar6+
	call   0x918c
	stm    #352,ar7
	stm    #145,brc
	call   0x9004
	stm    #356,ar7
	stm    #352,ar3
	stm    #141,brc
	rptb   0x9215
	ld     *ar7+,b
	stl    b,*ar3+
	ret
