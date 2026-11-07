; ROM6 0x36E1 FRAG_36E1 -- 15w, symbols.yaml data_word.
; Evidence: Bound 36E1-36EF (15w; exit B F073@36EE->2E64 + operand 36EF, byte-verified; exit scan clean); entry bc F820@36C6->36E1 byte-verified (chained from FRAG_36C2 interior); dispatcher-c
; ORIGIN 0x36E1
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#23
	bc     0x36f0,ntc
	andm   #4095,*(0x58f)
	orm    #12288,*(0x58f)
	call   0x2e2f
	b      0x2e64
