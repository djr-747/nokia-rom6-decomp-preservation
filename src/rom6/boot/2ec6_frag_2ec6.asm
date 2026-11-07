; ROM6 0x2EC6 FRAG_2EC6 -- 7w, symbols.yaml data_word.
; Evidence: Bound 2EC6-2ECC (7w, exit F073@2ECB->2E64 + operand 2ECC); entry bc F84C@2EC0 (byte-verified; head word E909 ld #9,b); SPLINTER of killed FRAG_2EC6 (overlap with BUILD_OPCODE_SPLIT
; ORIGIN 0x2EC6
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #9,b
	call   0x2e2f
	call   0x4590
	b      0x2e64
