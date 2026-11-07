; ROM6 0x44A6 FRAG_44A6 -- 9w, symbols.yaml data_word.
; Evidence: Bound 44A6-44AE (9w, exit FC00@44AE); entry bc F845@445E->44A6 (opcode-verified, in-zone source); zero F074/F274 callers whole-ROM; head 8A0A 8A09 8A08 1194 F330 000F 81F8 022D FC0
; ORIGIN 0x44A6
	.sect ".text"
	.mmregs
	.global _start
_start:
	popm   ag
	popm   ah
	popm   al
	ld     *ar4+,b
	and    #15,b
	stl    b,*(0x22d)
	ret
