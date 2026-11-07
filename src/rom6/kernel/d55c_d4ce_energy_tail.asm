; ROM6 0xD55C D4CE_ENERGY_TAIL -- 2w, symbols.yaml data_word.
; Evidence: Entered only via 0xD49B bc ntc; rpt-37 squra/macr loop; interior calld 0xE56D/0xE583/0xDB81; first exit retd FE00 @D55B +2 delays (Bound D55C-D55D, executed delay slots — wave-11 s
; ORIGIN 0xD55C
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar2
	stl    a,0x5e
