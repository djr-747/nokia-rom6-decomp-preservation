; ROM6 0x33BC FRAG_33BC -- 18w, symbols.yaml data_word.
; Evidence: Bound 33BC-33CD (18w, exit RET FC00@33CD); post-branch entry (WORKER_3364 exits F073@33BA->2E64); zero refs/callers whole-ROM; stm/mmap ALU + FF4C/FF44 portw pair; HYPOTHESIS leaf.
; ORIGIN 0x33BC
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar1,a
	stm    #1359,ar4
	and    #1,a,b
	andm   #32767,*ar4
	xc     2,bneq
	orm    #-32768,*ar4
	and    #2,a
	andm   #-257,*ar4
	xc     2,aneq
	orm    #256,*ar4
	ret
