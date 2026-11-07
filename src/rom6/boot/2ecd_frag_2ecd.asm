; ROM6 0x2ECD FRAG_2ECD -- 9w, symbols.yaml data_word.
; Evidence: Bound 2ECD-2ED5 (9w; exit BACC F4E2@2ED5 byte-verified, computed target unknown); entry bc F84F@2EBC->2ECD byte-verified (cond, retro-jump from WORKER_2E84 tail zone); abuts FRAG_2
; ORIGIN 0x2ECD
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #-20415,a
	pshm   ar1
	stlm   a,ar1
	stm    #1,ar0
	ld     *ar1,a
	popm   ar1
	bacc   a
