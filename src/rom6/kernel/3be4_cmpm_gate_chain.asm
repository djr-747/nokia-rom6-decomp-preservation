; ROM6 0x3BE4 CMPM_GATE_CHAIN -- 26w, symbols.yaml data_word.
; Evidence: Entry 60F8 250F 0022; bound 3BE4-3BFD; callers F074@3B82/3BBB/3C42; cmpm chain 250F/34BF/262B + bc- outs to 3BFE stub; HYPOTHESIS.
; ORIGIN 0x3BE4
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x250f),#34
	bc     0x3bfe,ntc
	cmpm   *(0x34bf),#3
	bc     0x3bfe,ntc
	cmpm   *(0x262b),#224
	bc     0x3bfe,tc
	bitf   *(0x3490),#256
	bc     0x3bfe,tc
	bitf   *(0x3490),#512
	bc     0x3bfe,tc
	ret
