; ROM6 0xAED9 DUALMAC_AED9 -- 19w (dark-gap wave-13).
; Evidence: No C: dual-parallel || form has no established C precedent (flagged). Post-? head (prev ends AED8; no exterior refs, entry unconfirmed). Bound AED9-AEEB (6x ld||masr dual-mac lanes; DP adds; adds; addc; sub; subs; subb; add ts; falls into AEEC regfield helper, tail note, aeec returns to caller). Words decode as valid code (not table: followed by accumulate + call-free fall-through; no table consumer found). Recombine-clean.
; ORIGIN 0xAED9
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar5-,a || masr *ar2,b
	ld     *ar5-,a || masr *ar3,b
	ld     *ar5-,a || masr *ar3-,b
	ld     *ar4+,a || masr *ar2+,b
	ld     *ar2+,a || masr *ar5-,b
	ld     *ar5-,a || masr *ar3+,b
	add    0x3f,a
	add    0x2f,a
	add    0x20,a
	add    0x30,a
	add    0x38,a
	add    0x27,a
	adds   *ar5+%,a
	addc   0x72,a
	sub    *ar0+0%,b
	subs   0x28,a
	subb   *+ar0(0xf074)%,b
	add    *+ar2,ts,b
