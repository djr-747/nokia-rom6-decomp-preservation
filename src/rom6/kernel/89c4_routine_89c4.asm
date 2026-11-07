; ROM6 0x89C4 ROUTINE_89C4 -- 39w, symbols.yaml data_word.
; Evidence: Bound 89C4-89EA (FC00@89EA objdump); callers F074 @8903/8981/89AF + F274 @88C9 (all objdump-verified call/calld); interior calls 89F4 @89D5/89DC, banz loops ->89DC/->89EB; 89EB-89F
; ORIGIN 0x89C4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x592
	stm    #2,ar0
	stm    #4348,ar1
	stm    #12440,ar2
	stm    #3,ar5
	stm    #0,ar3
	stm    #40,t
	st     t,*ar2+
	st     #0,*ar2+
	call   0x89f4
	and    #3,16,a
	sth    a,*ar2+0
	stm    #12,ar4
	call   0x89f4
	stm    #6,t
	and    #32767,16,a
	mpya   a
	add    #1,15,a
	sth    a,1,*ar2+
	banz   0x89dc,*ar4-
	banz   0x89eb,*ar5-
	ret
