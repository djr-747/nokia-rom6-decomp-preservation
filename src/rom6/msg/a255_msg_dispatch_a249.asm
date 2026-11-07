; ROM6 0xA255 MSG_DISPATCH_A249 -- 5w, symbols.yaml data_word.
; Evidence: CORRECTED per wave-2 (old note stale: no 10-word tail, no RET@A25E): head entry A249-A254 (F074 068E + reada, exit BACC F5E2@A254, objdump bacc b); table A255-A259 is DATA (5 BACC-
; ORIGIN 0xA255
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    *ar3-,*ar4+,a
	sub    *ar3-,*ar5+0%,a
	sub    *ar4-,*ar2-,a
	sub    *ar4-,*ar3+,a
	sub    *ar4+,*ar2+0%,a
