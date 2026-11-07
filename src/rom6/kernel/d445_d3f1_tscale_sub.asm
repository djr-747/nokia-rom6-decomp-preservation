; ROM6 0xD445 D3F1_TSCALE_SUB -- 2w, symbols.yaml data_word.
; Evidence: Entry mpy #5462 T-scale, stores DP+0x01/0x05; first exit retd FE00 @D444 +2 delays (Bound D445-D446, executed delay slots — wave-11 spill fix); caller F274 @D818 verified; block B 
; ORIGIN 0xD445
	.sect ".text"
	.mmregs
	.global _start
_start:
	sth    a,*(0xb65)
