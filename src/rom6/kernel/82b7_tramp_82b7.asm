; ROM6 0x82B7 TRAMP_82B7 -- 20w (overlap-split wave-12).
; Evidence: Bound 82B7-82CA; entry call F074 066E (dark); exterior caller call @81CD (810A-region, objdump-verified); bcd 0x82CB,tc interior; calld 0x82D4/@82C2 + calld 0x82FF/@82C6; exit ret FC00 @82CA. Carved from 81f1_sub232_810a.asm tail (deleted). Recombine-clean.
; ORIGIN 0x82B7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x66e
	stm    #10884,ar2
	bitf   *(0x264f),#1
	bcd    0x82cb,tc
	stm    #10892,ar0
	calld  0x82d4
	stm    #-8966,ar6
	calld  0x82ff
	stm    #-8966,ar6
	ret
