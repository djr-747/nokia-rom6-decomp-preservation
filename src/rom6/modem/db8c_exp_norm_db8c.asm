; ROM6 0xDB8C EXP_NORM_DB8C -- 53w, symbols.yaml data_word.
; Evidence: Entry E721 770E 0010 771A 0027 F4B9; caller F274 @D23F verified; first exit retd FE00 @DBC0 +delays (Bound DBC1-DBC2, executed delay slots — wave-11 spill fix) F495/F48F abutting e
; Pool: mpyr 0x7c,a x2 (MPY-with-round: no catalog row, no leaf anywhere in the oracle). Secondaries grounded-or-flagged (sqdst/op_sqdst core; squr/op_squr_acc; ld-ts row+op_ld_smem leaf; sub-shifts; mac-lk; exp/norm/sat/abs; rptbd flagged). stays .asm, bytes verified.
; ORIGIN 0xDB8C
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar2,ar1
	stm    #16,t
	stm    #39,brc
	rsbx   st0,ovb
	rptbd  0xdb97
	mvmm   ar1,ar2
	ld     #0,b
	ld     *ar2+,ts,a
	sqdst  *ar2,*ar2
	bc     0xdba0,bnov
	addm   #-1,0x0e
	bd     0xdb92
	stm    #39,brc
	st     t,0x7a
	ld     #1,a
	add    b,a
	exp    a
	st     t,0x7b
	norm   a
	sth    a,0x7c
	squr   a,a
	ld     #12288,16,b
	sub    a,-3,b
	mac    0x7c,#24576,b
	ld     #1,a
	and    0x7b,a
	sth    b,0x7c
	bc     0xdbb8,aeq
	stm    #23170,t
	mpyr   0x7c,a
	sth    a,0x7c
	addm   #-1,0x7b
	stm    #10362,t
	mpyr   0x7c,a
	ld     #16,b
	sub    0x7a,b
	sub    0x7b,-1,b
	stlm   b,t
	retd
