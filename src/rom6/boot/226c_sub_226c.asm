; ROM6 0x226C SUB_226C -- 22w, symbols.yaml program_word.
; Evidence: Exterior call x5 (0x303B/0x450F/0x451A/0x4522 + in-gap); call-2282 + bc-gated idle-wait/2E39-call retry loop + ret; no other entries, evidenced, flagged.
; ORIGIN 0x226C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call 0x2282
	bc 0x2271,ntc
	ret
	ssbx st1,intm
	bitf *(0x866),#2
	bc 0x227b,tc
	rsbx st1,intm
	idle 1
	b 0x2271
	rsbx st1,intm
	pshm ar2
	call 0x2e39
	popm ar2
	b 0x226c
