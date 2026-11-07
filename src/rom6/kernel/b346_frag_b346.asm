; ROM6 0xB346 FRAG_B346 -- 18w, symbols.yaml data_word.
; Evidence: Bound B346-B357 (18w, exit FC00@B357); bacc-table arm; rc+cc variant; HYPOTHESIS.
; ORIGIN 0xB346
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	call   0xa361
	rc     aneq
	call   0xa4de
	call   0xa482
	call   0xa5e1
	call   0xa679
	call   0xa7b7
	call   0xa7eb
	ret
