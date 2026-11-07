; ROM6 0x538D DISPATCH_SLED_A -- 8w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x538D
	.sect ".text"
	.mmregs
	.global _start
_start:
	b      0x5395
	b      0x53eb
	b      0x5434
	b      0x544a
