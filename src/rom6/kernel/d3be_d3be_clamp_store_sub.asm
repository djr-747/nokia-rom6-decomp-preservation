; ROM6 0xD3BE D3BE_CLAMP_STORE_SUB -- 49w, symbols.yaml data_word.
; Evidence: Entry bitf *(0xA60) min/max lane; interior calld 0xD39E @D3D4; first exit retd FE00 @D3EE +2 delays (Bound D3EF-D3F0, executed delay slots — wave-11 spill fix); caller F274 @D834 c
; ORIGIN 0xD3BE
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0xa60),#1
	bcd    0xd3e1,ntc
	ld     #4,a
	and    0x68,a
	bc     0xd3d4,aneq
	mvdm   0x3000,ar2
	ld     0x59,a
	ld     *ar2(0xfba6),14,b
	bc     0xd3d1,aeq
	ld     0x5c,16,a
	min    b
	sth    b,0x5c
	b      0xd3e4
	calld  0xd39e
	stm    #3114,ar2
	ld     0x5b,16,a
	min    a
	mvdm   0xb5a,ar2
	sth    a,0x5b
	bd     0xd3e4
	mpya   *ar2(0xfc34)
	ld     #0,b
	xc     1,aeq
	sth    b,0x5c
	sth    b,*(0x3003)
	ld     #4096,16,a
	min    b
	stm    #3114,ar2
	rpt    #3
	mvkd   0xc2b,*ar2+
	retd
