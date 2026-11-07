; ROM6 0xA3BE FRAG_A3BE -- 7w, symbols.yaml data_word.
; Evidence: Bound A3BE-A3C4 (exit RET FC00@A3C4 objdump, rc aeq/calld 3E53 interior); entry F84D@A3AC (branch- entry); starts after STUB_A361 end A3BD, no overlap; sibling stub A3CE-A3D4 (no s
; ORIGIN 0xA3BE
	.sect ".text"
	.mmregs
	.global _start
_start:
	rc     aeq
	calld  0x3e53
	andm   #-3073,*ar2
	ld     #0,b
	ret
