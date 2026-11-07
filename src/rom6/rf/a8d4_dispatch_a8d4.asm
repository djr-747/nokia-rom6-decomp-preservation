; ROM6 0xA8D4 DISPATCH_A8D4 -- 42w, symbols.yaml data_word.
; Evidence: Entry F074 0666 61F8 051C 0040 F830; bound A8D4-A8FD (FC00@A8FD, adjacent A8FE); caller F074@AFEC (objdump-verified call 0xa8d4); interior calls 0666/B750/9FCF/C5F9/A109/AB78 (all 
; ORIGIN 0xA8D4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x666
	bitf   *(0x51c),#64
	bc     0xa8fd,tc
	bitf   *(0x2b08),#3
	bc     0xa8f9,ntc
	st     #12854,*(0x337d)
	mvkd   0x54a,*(0x337b)
	ld     #159,a
	call   0xb750
	call   0x9fcf
	st     #12854,*(0x337c)
	call   0xc5f9
	bitf   *(0x577),#4096
	ccd    0xbcfc,tc
	stm    #12854,ar1
	call   0xa109
	calld  0xab78
	stm    #12854,ar2
	ret
