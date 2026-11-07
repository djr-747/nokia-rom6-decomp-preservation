; ROM6 0x3D3B FRAG_3D3B -- 2w, symbols.yaml data_word.
; Evidence: Bound 3D3B-3D3C (2w micro: out-call F074 063A@3D3B + falls into ROUTINE_3D3D head — tail-frag abut, not a routine); entry cc F920@7AE8->3D3B byte-verified (cond ntc call, exterior 
; ORIGIN 0x3D3B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x63a
