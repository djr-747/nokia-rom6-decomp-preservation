; ROM6 0x27EB FRAME_ISR_HEAD_27EB -- 21w, symbols.yaml program_word.
; Evidence: FRAME_ISR sample-combine head per roms/rom6/ivt.md (ST1 mode prologue, pa2/pa1 strobes, ~(port2)&(port1) combine, BITF dispatch); entry by fallthrough from the abutting 27E9 slot (27EA-27EB instruction boundary); exits bc 0x296A (owned tail) + fallthrough 27FF->0x2800 into rf/2800_stretch_2800 (evidenced by its header).
; ORIGIN 0x27EB
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    st1,a ; @0x27EB 4807
	and    #8192,a ; @0x27EC f030
	or     #18688,a ; @0x27EE f040
	stlm   a,st1 ; @0x27F0 8807
	stm    #542,ar2 ; @0x27F1 7712
	portr  2,*ar2 ; @0x27F3 7482
	ld     *ar2,a ; @0x27F5 1082
	cmpl   a ; @0x27F6 f493
	portr  1,*ar2 ; @0x27F7 7482
	and    *ar2,a ; @0x27F9 1882
	and    #4096,a,b ; @0x27FA f130
	bc     0x296a,bneq ; @0x27FC f84c
	and    #28,a,b ; @0x27FE f130
