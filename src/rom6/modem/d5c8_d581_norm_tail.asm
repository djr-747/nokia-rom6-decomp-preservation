; ROM6 0xD5C8 D581_NORM_TAIL -- 2w, symbols.yaml data_word.
; Evidence: Entered only via 0xD57A bc bneq; norm/exp/subc chain; interior calld 0xE54B @D5A7; rptbd fill; first exit retd FE00 @D5C7 +2 delays (Bound D5C8-D5C9, executed delay slots — wave-11
; ORIGIN 0xD5C8
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdk   *ar2,0xb58
