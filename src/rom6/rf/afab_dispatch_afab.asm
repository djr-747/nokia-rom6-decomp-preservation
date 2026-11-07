; ROM6 0xAFAB DISPATCH_AFAB -- 10w, symbols.yaml data_word.
; Evidence: Entry F074 B0F5 (byte-verified); bound AFAB-AFB4 (exit bacc F5E2@AFB4); 10-word jtab AFB5-AFBE follows (bytes verified: AFBF AFD3 AFF9 B017 B04B B050 B062 B080 B0BD B0C2); third ba
; ORIGIN 0xAFAB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xb0f5
	ldm    ar2,a
	add    #-20555,a
	and    #-1,a
	reada  *(0xb)
	bacc   b
