; ROM6 0xA89B FRAG_A89B -- 10w, symbols.yaml data_word.
; Evidence: Bound A89B-A8A4 (10w; exit RET FC00@A8A4 byte-verified); post-RET head (FC00@A89A, zero ext refs); interior bc F820@A89E->A8A5 (targets past-RET remainder — mid-entry to micro-FRAG
; ORIGIN 0xA89B
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#4096
	bc     0xa8a5,ntc
	ld     *(0x3083),a
	bc     0xa8b9,aeq
	ret
