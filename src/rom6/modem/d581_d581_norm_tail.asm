; ROM6 0xD581 D581_NORM_TAIL -- 71w, symbols.yaml data_word.
; Pool: sqdst *ar2,*ar2 (E200, wave-12). Dual-memory X/Y step modes plus the SXM/FRCT/OVM status tuple are all dark in-span (no ST1 setup anywhere in D581-D5C7; SXM=1 not provable per the bfaa rule), and the E54B-calld lane shifts by entry-residue ASM (ld 0x04,asm 3204). Joint blockers: mpya b/a (F58C/F48C), mac *ar2,*ar3,b,a (B201), ld-asm shift. Full trace: exp/norm/adds/sth head (plain STH 0x82xx, no ASM input), rptbd fill [D591,D592] after once-executed ld/squr pair, bc-agtest to the D599 subc lane (rpt #14 subc, subc_step32 shape), calld E54B with 1-word delays (ld a,asm; ld #0,dp, both complete, WORD-count clean), banzd delays (sfta; adds), rptbd MAC fill, retd with delays in D5C8 (cross-span).
; Evidence: Entered only via 0xD57A bc bneq; norm/exp/subc chain; interior calld 0xE54B @D5A7; rptbd fill; first exit retd FE00 @D5C7 +2 delays (Bound D5C8-D5C9, executed delay slots — wave-11
; ORIGIN 0xD581
	.sect ".text"
	.mmregs
	.global _start
_start:
	exp    b
	st     #-32768,0x09
	st     t,0x08
	addm   #-1,0x08
	ld     0x08,t
	norm   b
	adds   0x09,b
	stm    #38,brc
	sth    b,0x06
	rptbd  0xd592
	ld     *ar2+,14,a
	squr   a,b
	ld     *ar2+,14,a
	sqdst  *ar2,*ar2
	bc     0xd599,bneq
	banz   0xd5ca,*ar6
	b      0xd5b5
	exp    b
	ld     0x06,16,a
	norm   b
	adds   0x09,b
	sth    b,0x05
	rpt    #14
	subc   0x05,a
	stl    a,0x04
	ld     0x04,7,a
	ldm    t,b
	sub    0x08,b
	stl    b,0x04
	ld     0x04,asm
	calld  0xe54b
	ld     a,asm
	ld     #0,dp
	ld     #96,dp
	banzd  0xd5ca,*ar6
	sfta   a,9
	adds   0x09,a
	stm    #3276,t
	mpya   b
	and    #-1,16,b
	stm    #39,brc
	stm    #12295,ar3
	stm    #12292,ar2
	ld     #0,asm
	mvkd   0xb58,*ar2
	rptbd  0xd5c6
	st     #29491,*ar3
	mac    *ar2,*ar3,b,a
	st     a,*ar2 || ld     *ar4,t
	mpya   a
	sfta   a,3
	sth    a,*ar4+
	retd
