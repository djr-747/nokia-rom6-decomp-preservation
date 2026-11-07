; ROM6 0x7C9E COUNTER_STEP_7C9E -- 7w, symbols.yaml data_word.
; Evidence: Entry 1082 F000 0001 F030 0003 8082; first exit ret FC00 @7CA4 (7 words ld/add/and#3/stl); callers F274 calld @7D2C/7E43/807A/8105/81ED objdump-verified; HYPOTHESIS.
; ORIGIN 0x7C9E
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,a
	add    #1,a
	and    #3,a
	stl    a,*ar2
	ret
