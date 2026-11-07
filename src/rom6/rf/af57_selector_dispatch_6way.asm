; ROM6 0xAF57 SELECTOR_DISPATCH_6WAY -- 13w, symbols.yaml data_word.
; Evidence: Post-RET head (ret AF56); entry F074 0690 + F074 AF92 (selector helper, AR2 out, ret AFAA); A=AR2-20636, reada *(0xb), first exit bacc b @AF63; bound AF57-AF63; 6-way table dispatc
; ORIGIN 0xAF57
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x690
	call   0xaf92
	ld     #0,b
	ldm    ar2,a
	add    #-20636,a
	and    #-1,a
	reada  *(0xb)
	bacc   b
