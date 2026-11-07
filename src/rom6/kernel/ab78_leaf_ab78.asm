; ROM6 0xAB78 LEAF_AB78 -- 10w, symbols.yaml data_word.
; Evidence: Entry F074 06A4 61F8 0577 0001 FC20; bound AB78-AB81 (FC00@AB81, exact gap end); callers F274 @A724/A8F9/AA17 (verified); interior call 06A4; cond bitf *(0x577)#1; HYPOTHESIS tiny 
; ORIGIN 0xAB78
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6a4
	bitf   *(0x577),#1
	rc     ntc
	rptz   a,#159
	stl    a,*ar2+
	ret
