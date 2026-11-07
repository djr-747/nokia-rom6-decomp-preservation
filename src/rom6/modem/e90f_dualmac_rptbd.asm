; ROM6 0xE90F DUALMAC_RPTBD -- 20w, symbols.yaml data_word.
; Evidence: Entry 4482 4183 C391 CA18 3D82 C780 F272 E921; 4x callers F074 @E95A/E971/E988/E99A; first-RET @E922 (20w); HYPOTHESIS.
; Pool: E629 st b,*ar3+ || ld *ar4,t (ST||LD-T parallel: no catalog row, gap confirmed over all 347 OPCODE_MASKED rows). Secondaries grounded (ST||ADD/SUB/MPY rows + op_st_parallel leaves; dual-mac op_mac_dual; mas op_mas_smem; ld-T op_ld_t_smem; rptbd flagged). stays .asm, bytes verified.
; ORIGIN 0xE90F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	rptbd  0xe921
	st     b,*ar3+ || ld     *ar4,t
	mpy    *ar3+,a
	mac    *ar5+,*ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,*ar4+,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	ld     *ar4,t
	st     b,*ar2+ || mpy    *ar3+,a
	ret
