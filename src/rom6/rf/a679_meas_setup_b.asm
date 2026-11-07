; ROM6 0xA679 MEAS_SETUP_B-entry0 -- 14w (overlap-split wave-12).
; Evidence: Bound A679-A686 (call 65C; ld; rc aeq; ld #1,b; call 4BA8; ld #0,b; stl; retd @A684 + delays A685-A686). retd is an UNCONDITIONAL delayed return (no fall-through into A687; the b.c sled Entry-0 return is correct). Former tail A687-A6AD duplicated the a687 span (owned there; deleted from this file). C sled intent in a679_meas_setup_b.c (EXPECT unchanged, now verified across this vehicle + a687 vehicle). Recombine-clean.
; ORIGIN 0xA679
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65c
	ld     *(0x262e),a
	rc     aeq
	ld     #1,b
	call   0x4ba8
	ld     #0,b
	stl    b,*(0x262e)
	retd
	stl    b,*(0x2614)
