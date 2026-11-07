; ROM6 0x4A4B FRAG_4A4B -- 24w, symbols.yaml data_word.
; Evidence: Bound 4A4B-4A62 (24w, exit BD F273@4A5F->4AE0 + delays 4A60-4A62, end=pc+3); 6 inbound branch joins, zero callers; head 60F8 250F 0022 + F845 4A63; BD target 4AE0 unresolved (4AE0-
; ORIGIN 0x4A4B
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x250f),#34
	bc     0x4a7b,ntc
	cmpm   *(0x34bf),#3
	bc     0x4a6b,ntc
	sub    *(0x366f),b,a
	bc     0x4a63,aeq
	sub    *(0x37b0),b,a
	bc     0x4a67,aeq
	bd     0x4ae0
	st     #3,*ar5
