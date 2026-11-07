; ROM6 0x7FB5 SUB32_7F95 -- 17w (overlap-split wave-12).
; Evidence: Bound 7FB5-7FC5 (own lanes: ld/rptb-loop/mar/ret @7FBF; ld/call 7FB7/mvmm/ret @7FC5). Former tail 7FC6-7FD3 duplicated the 7fc6_sub46_7fc6 span head (owned there, C-verified) -- trimmed. Post-unconditional-b head (F073 b @7F93). Entry F074 059E 7715 0006. Recombine-clean.
; ORIGIN 0x7FB5
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @7FB5 f120 ld     #-21846,b (leading operand 0x7FB4 homed in the 7FB3 span, overlap-corrected wave-12)
	ld     #-21846,b
	; @7FB7 771a stm    #7,brc
	stm    #7,brc
	; @7FB9 f072 rptb   0x7fbd
	rptb   0x7fbd
	; @7FBB 1082 ld     *ar2,a
	ld     *ar2,a
	; @7FBC f280 and    b,a
	and    b,a
	; @7FBD 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @7FBE 6d8a mar    *ar2-
	mar    *ar2-
	; @7FBF fc00 ret
	ret
	; @7FC0 f120 ld     #21845,b
	ld     #21845,b
	; @7FC2 f074 call   0x7fb7
	call   0x7fb7
	; @7FC4 e721 mvmm   ar2,ar1
	mvmm   ar2,ar1
	; @7FC5 fc00 ret
	ret
