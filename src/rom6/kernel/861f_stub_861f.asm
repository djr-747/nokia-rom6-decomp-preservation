; ROM6 0x861F STUB_861F -- 8w (overlap-split wave-12).
; Evidence: Bound 861F-8626 (mar/dld/call 8627/dst/ret @8626); zero F074/F274 callers (entry ambiguous per prior pool note -- calls land on the ret word 861E; stub may be unreachable, flagged); carved from 861e pool bundle (leading ret owned by 8611 exit; rptb head 8627-862C owned by 8627; bundle file deleted). C intent in 861f_stub_861f.c. Recombine-clean.
; ORIGIN 0x861F
	.sect ".text"
	.mmregs
	.global _start
_start:
	mar    *ar2-
	dld    *(0x60),a
	call   0x8627
	dst    a,*(0x60)
	ret
