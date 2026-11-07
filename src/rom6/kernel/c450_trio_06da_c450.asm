; ROM6 0xC450 TRIO_06DA_C450 -- 16w, symbols.yaml data_word.
; Evidence: Entry F074 06DA; bounds C450-C45F + C460-C470 + C471-C48B (call C53D@C47A); callers BE04/BE0D calld->C450, BDF6/BDFB->C460, BE13/BE1B calld->C471; BRC 87/127 + RPTBD fills; HYPOTHE
; ORIGIN 0xC450
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6da
	stm    #87,brc
	ssbx   st1,ovm
	ld     #23,a
	sub    0x44,a
	stlm   a,t
	rptbd  0xc45e
	stm    #2,ar0
	ld     *ar2+0,ts,a
	adds   0x42,a
	sth    a,*ar3+
	ret
