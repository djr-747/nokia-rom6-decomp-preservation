; ROM6 0xA249 MSG_DISPATCH_A249 -- 12w, symbols.yaml data_word.
; Evidence: CORRECTED per wave-2 (old note stale: no 10-word tail, no RET@A25E): head entry A249-A254 (F074 068E + reada, exit BACC F5E2@A254, objdump bacc b); table A255-A259 is DATA (5 BACC-
; ORIGIN 0xA249
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x68e
	ld     #0,b
	ld     *(0x574),a
	add    #-23979,a
	and    #-1,a
	reada  *(0xb)
	bacc   b
