; ROM6 0x3EBD FIR_COEFF_TABLE -- 1w, symbols.yaml program_word.
; Evidence: Matched-filter coefficients for SAMPLE_ISR_ENTRY. Length open (8 taps implied, unconfirmed).
; ORIGIN 0x3EBD
	.sect ".text"
	.mmregs
	.global _start
_start:
	portw  *(0xc),49
