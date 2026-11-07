; ROM6 0x644B SUB13_644A-tail -- 13w (overlap-split wave-12).
; Evidence: Words 644B-6457 (st #0,*ar5; stm #2325,ar2; ld *ar6,a; add *ar2+,a; stm #12247,ar3; stl; mvdd; ld; sub #51,a). Word0 ret FC00 @644A owned by 643e_sub13_643e.asm (643e exit; 644a.c models it verified-not-modeled). Interior entry of SUB13_643E; falls through to 6458 MPYA ladder. Recombine-clean.
; ORIGIN 0x644B
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #0,*ar5
	stm    #2325,ar2
	ld     *ar6,a
	add    *ar2+,a
	stm    #12247,ar3
	stl    a,*ar3+
	mvdd   *ar2,*ar3-
	ld     *ar3,a
	sub    #51,a

