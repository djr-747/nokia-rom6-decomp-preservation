; ROM6 0xA8A5 FRAG_A8A5 -- 12w, symbols.yaml data_word.
; Evidence: Bound A8A5-A8B0 (6w; exit RET FC00@A8B0 byte-verified; micro-span); entry interior bc F820@A89E-> A8A5 (from FRAG_A89B span, exterior to this span — valid mid-entry); head 7713... 
; ORIGIN 0xA8A5
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x3082),a
	or     *(0x2ef7),a
	bc     0xa8b9,aneq
	ld     *(0x3083),-1,a
	bc     0xa8b9,aeq
	ret
