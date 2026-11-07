; ROM6 0x2289 SUB_2289 -- 81w, symbols.yaml program_word.
; Evidence: Exterior call @0x2DEA (PROM); ldu/sub/add sample lanes, rptb fill, interior call-22CF, bgeq/aeq/beq joins, cmpm gate, calld-2262 tail; interior frag_22CF lane (22CF-22D9) in-span; no other entries, evidenced, flagged.
; ORIGIN 0x2289
	.sect ".text"
	.mmregs
	.global _start
_start:
	call 0x59c
	ldu *(0x87b),a
	sub *(0x87e),a
	sub #2048,a
	ld #0,b
	bc 0x22b4,aeq
	ldu *(0x87e),a
	add #2048,a
	stlm a,ar2
	ldu *(0x87d),b
	bc 0x22b4,beq
	ldu *(0x87f),a
	sub a,b
	bc 0x22a5,bgeq
	ldu *(0x87d),a
	ld #0,b
	sub #1,a
	stlm a,brc
	ldu *(0x87b),a
	stlm a,ar3
	rptb 0x22ae
	ldu *ar2+,a
	stl a,*ar3+
	ldm ar3,a
	mvmd bl,0x87d
	mvmd al,0x87b
	ld *(0x872),a
	xor #4,a
	call 0x22cf
	bc 0x22bd,aeq
	ret
	stm #1334,ar2
	ld *ar2+,asm
	ld #1,a
	ld a,asm
	or *ar2,a
	stl a,*ar2
	cmpm *(0x536),#6
	rc ntc
	call 0x59c
	calld 0x2262
	stm #5,ar2
	ret
	.mmregs
	.global _start
	stm #2162,ar1
	st #0,*ar1
	orm #8,*(0x29)
	andm #-9,*(0x29)
	ret
