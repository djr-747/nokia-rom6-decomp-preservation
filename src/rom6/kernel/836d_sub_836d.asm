; ROM6 0x836D SUB_836D -- 31w, symbols.yaml data_word.
; Evidence: Entry 4917 F84C 837C (ldm AR7; bc bneq); zero callers; interior uncond b 0x8384 @837A; 837C lane (call 7FC0/stm/calld 7F95/stm) falls into 8384 join (calld 7FC6/stm/orm/ret @838B); bound 836D-838B (extended wave-12 from 15w; tail words from deleted 836c draft). C intent in 836d_sub_836d.c. Recombine-clean.
; ORIGIN 0x836D
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar7,b
	bc     0x837c,bneq
	calld  0x82d4
	stm    #-8966,ar6
	stm    #-20100,ar6
	calld  0x7f95
	stm    #-12,t
	b      0x8384
	; @837C f074 call   0x7fc0
	call   0x7fc0
	; @837E 7716 stm    #-20100,ar6
	stm    #-20100,ar6
	; @8380 f274 calld  0x7f95
	calld  0x7f95
	; @8382 770e stm    #-4,t
	stm    #-4,t
	; @8384 f274 calld  0x7fc6
	calld  0x7fc6
	; @8386 7712 stm    #10884,ar2
	stm    #10884,ar2
	; @8388 69f8 orm    #512,*(0x2a87)
	orm    #512,*(0x2a87)
	; @838B fc00 ret
	ret
