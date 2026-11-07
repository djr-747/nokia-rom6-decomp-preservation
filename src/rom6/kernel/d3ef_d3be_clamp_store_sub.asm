; ROM6 0xD3EF D3BE_CLAMP_STORE_SUB -- 2w, symbols.yaml data_word.
; Evidence: Entry bitf *(0xA60) min/max lane; interior calld 0xD39E @D3D4; first exit retd FE00 @D3EE +2 delays (Bound D3EF-D3F0, executed delay slots — wave-11 spill fix); caller F274 @D834 c
; ORIGIN 0xD3EF
	.sect ".text"
	.mmregs
	.global _start
_start:
	sth    b,0x5b
	sth    b,*ar2
