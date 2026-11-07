; ROM6 0xB11C DISPATCH_B11C -- 13w, symbols.yaml data_word.
; Evidence: Bound B11C-B128 (13w, exit bacc F5E2@B128 objdump bacc b); post-RET head; selector idiom F074 0686 + F074 AF92 + E900/4812/F000 B129/F030 FFFF/7EF8 000B (same AR2/reada *(0xb) fami
; ORIGIN 0xB11C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x686
	call   0xaf92
	ld     #0,b
	ldm    ar2,a
	add    #-20183,a
	and    #-1,a
	reada  *(0xb)
	bacc   b
