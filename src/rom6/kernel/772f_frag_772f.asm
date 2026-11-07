; ROM6 0x772F FRAG_772F -- 31w, symbols.yaml data_word.
; Evidence: Bound 772F-774D (31w; exit RET FC00@774D byte-verified, exit scan clean); post-RET head (FC00@772E) + interior-projection call F274@749E->773B (in-span, calld into body — execution
; ORIGIN 0x772F
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @772F 25c2 mpyu   *ar2-%,b
	mpyu   *ar2-%,b
	; @7730 2dde mas    *ar6+0%,b
	mas    *ar6+0%,b
	; @7731 43ba sub    *ar2+0B,16,b
	sub    *ar2+0B,16,b
	; @7732 47b4 rpt    *ar4+0
	rpt    *ar4+0
	; @7733 1ae4 or     *ar4(0x4eb0),a
	or     *ar4(0x4eb0),a
	; @7735 a7d8 macsu  *ar3+0%,*ar2+,b
	macsu  *ar3+0%,*ar2+,b
	.word 0xEF12 ; UNKNOWN to objdump
	; @7737 b962 mas    *ar4-,*ar4,a,b
	mas    *ar4-,*ar4,a,b
	; @7738 040f add    0x0f,ts,a
	add    0x0f,ts,a
	; @7739 2d45 mas    0x45,b
	mas    0x45,b
	; @773A 761b st     #-3980,0x1b
	st     #-3980,0x1b
	; @773C 059e add    *+ar6,ts,b
	add    *+ar6,ts,b
	; @773D e907 ld     #7,b
	ld     #7,b
	; @773E e725 mvmm   ar2,ar5
	mvmm   ar2,ar5
	; @773F e736 mvmm   ar3,ar6
	mvmm   ar3,ar6
	; @7740 e800 ld     #0,a
	ld     #0,a
	; @7741 47f8 rpt    *(0xb)
	rpt    *(0xb)
	; @7743 b089 mac    *ar2+,*ar3+,a
	mac    *ar2+,*ar3+,a
	; @7744 4e94 dst    a,*ar4+
	dst    a,*ar4+
	; @7745 6dee mar    *+ar6(0x2)
	mar    *+ar6(0x2)
	; @7747 f310 sub    #2,b
	sub    #2,b
	; @7749 fa4e bcd    0x7740,bgt
	bcd    0x7740,bgt
	; @774B e752 mvmm   ar5,ar2
	mvmm   ar5,ar2
	; @774C e763 mvmm   ar6,ar3
	mvmm   ar6,ar3
	; @774D fc00 ret
	ret
