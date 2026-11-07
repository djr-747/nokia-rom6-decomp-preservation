; ROM6 0xC460 TRIO_06DA_C450 -- 17w, symbols.yaml data_word.
; Evidence: Entry F074 06DA; bounds C450-C45F + C460-C470 + C471-C48B (call C53D@C47A); callers BE04/BE0D calld->C450, BDF6/BDFB->C460, BE13/BE1B calld->C471; BRC 87/127 + RPTBD fills; HYPOTHE
; ORIGIN 0xC460
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6da
	stm    #127,brc
	mvdm   0x3148,ar3
	ld     0x41,16,b
	mvmm   ar3,ar2
	ld     #-1,asm
	mar    *ar3+
	rptbd  0xc46f
	ld     *ar2,16,a
	add    b,a
	st     a,*ar2+ || ld     *ar3+,a
	add    b,a
	ret
