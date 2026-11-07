; ROM6 0x7AB1 FRAG_7AB1 -- 45w, symbols.yaml data_word.
; Evidence: Bound 7AB1-7ADD (exit F073@7ADC->7AE5); branch-entry from live lane b@7A2E->7AB1 (other F073 entries @7A59/7A5D/7A60/7A8E/7AA0 sit in post-7A49 dead zone; no whole-ROM F073 entries
; ORIGIN 0x7AB1
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x250f),#34
	bc     0x7ae5,ntc
	cmpm   *(0x34bf),#1
	bc     0x7ae5,tc
	cmpm   *(0x34bf),#4
	bc     0x7ae5,tc
	stm    #9782,ar3
	cmpm   *(0x34bf),#3
	bc     0x7ae5,ntc
	ld     *ar1,a
	sub    #224,a
	bc     0x7ade,aeq
	bitf   *(0x3490),#128
	bc     0x7ae5,ntc
	bitf   *(0x3490),#256
	bc     0x7ad8,ntc
	stm    #13502,ar3
	mar    *ar0+
	andm   #-129,*(0x3490)
	b      0x7ae5
