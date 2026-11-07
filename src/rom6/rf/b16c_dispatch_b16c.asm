; ROM6 0xB16C DISPATCH_B16C -- 11w, symbols.yaml data_word.
; Evidence: Bound B16C-B176 (11w, exit bacc F5E2@B176); post-RET head (after FC00@B16B); same selector idiom (F074 AF92 + E900/4812/F000 B177/...); 6-way table B177-B17C = B17D/B1ED/B21F/B26E/
; ORIGIN 0xB16C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xaf92
	ld     #0,b
	ldm    ar2,a
	add    #-20105,a
	and    #-1,a
	reada  *(0xb)
	bacc   b
