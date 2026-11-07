; ROM6 0x4433 DISPATCH_TABLE_6 -- 6w, symbols.yaml data_word.
; Evidence: 6 words 4439 4439 4453 4444 446D 4474 @4433-4438 (bytes verified) between RET@4432 and code@4439; consumer add #4433 @4402 + reada @4404 + cala b @4406 (routine 0x43EA). Bound 4433
; ORIGIN 0x4433
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0x4439
	.word 0x4439
	.word 0x4453
	.word 0x4444
	.word 0x446D
	.word 0x4474
