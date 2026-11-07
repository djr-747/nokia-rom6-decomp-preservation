; ROM6 0x864E MSG_BUILDER_864E -- 1w, symbols.yaml program_word.
; Evidence: CALL 0x592, CALL 0x8A45, RET at 0x8652. Same three caller groups.
; Wave-13: lane @8650-8652 annexed (gap orphan; call 8A45 + ret).
; ORIGIN 0x864E
	.sect ".text"
	.global _start
_start:
	call   0x592
	call   0x8a45
	ret
