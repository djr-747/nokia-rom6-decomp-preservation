; ROM6 0x643E SUB13_643E -- 13w, symbols.yaml data_word.
; Evidence: Post-RET head (ret @643D); entry 60F8 053C 0004 cmpm *(0x53C),#4; ZERO true CALLers (sole ref F820 bc ntc @6425); first exit ret @644A len 13; inner F074 697F @6448; branch-only pr
; ORIGIN 0x643E
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x53c),#4
	rc     ntc
	st     #0,*(0x2615)
	mvkd   0x2652,*(0x2617)
	call   0x697f
	ret
