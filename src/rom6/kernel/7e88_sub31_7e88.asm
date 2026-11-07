; ROM6 0x7E88 SUB31_7E88 -- 30w, symbols.yaml data_word.
; Evidence: Post-retd head (retd @7E85 + delays 7E86/7E87); entry F074 059E 7719 0002; first exit ret @7EA6 len 31 (inner calld 7EA7 @7E92 + entry-call 059E); callers F074 @7E58 + F274 @7D04/7. Ret @0x7EA6 owned by the 7EA6 span (fall-through abut, overlap-corrected wave-12; span now 7E88-7EA5).
; ORIGIN 0x7E88
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #2,bk
	stm    #96,ar4
	stm    #97,ar5
	stm    #7,brc
	calld  0x7ea7
	stm    #3,ar0
	ld     *ar3,b
	rptb   0x7e9c
	ld     *ar5,16,a
	rol    a
	sth    a,*ar5+%
	rol    b
	stl    b,*ar3-
	ld     *ar3,b
	banzd  0x7e97,*ar0-
	stm    #7,brc
	banz   0x7e92,*ar1-
	mar    *ar3+
	; ret @0x7EA6 owned by the 7EA6 span (fall-through abut, overlap-corrected wave-12)
