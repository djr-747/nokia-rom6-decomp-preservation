; ROM6 0x516A ROUTINE_516A -- 38w, symbols.yaml data_word.
; Evidence: Bound 516A-518F (38w; exit RETD FE00@518D + and delay 518E-518F byte-verified, exit scan otherwise clean); entry call F074@4D70->516A byte-verified (far forward call from 4D-worker zone); exterior exits bc F830@5176->51D4 + bc F84D@517F->51D4 (MISS_SINK_51D4) + bc F84D@5183->51CC + bc F830@5188->51CC (HIT_51CC) + bc F845@518A->5190 (LANE_36F).
; ORIGIN 0x516A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	cmpm   *(0x2f1f),#160
	ld     #0,b
	rc     ntc
	stm    #9767,ar4
	bitf   *(0x2f5c),#-256
	bc     0x51d4,tc
	ld     *(0x2f60),-8,a
	and    #15,a
	sub    #15,a,b
	bc     0x51d4,beq
	sub    #8,a,b
	bc     0x51cc,beq
	bitf   *(0x54f),#1024
	bc     0x51cc,tc
	bc     0x5190,aeq
	ld     *ar4,b
	retd
	and    #256,b
