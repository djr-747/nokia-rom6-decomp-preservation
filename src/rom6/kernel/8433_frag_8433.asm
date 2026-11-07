; ROM6 0x8433 FRAG_8433 -- 22w, symbols.yaml data_word.
; Evidence: Bound 8433-8448 (22w; exit RET FC00@8448 byte-verified, exit scan clean); entries branch-only bc F820@841E/8423->8436 + F820@8428->8433 head + B F073@8431->843A; interior rptb F072
; ORIGIN 0x8433
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #2048,*(0x2648)
	stm    #9800,ar4
	stm    #9592,ar3
	orm    #16,*ar4
	ldu    *ar2+%,a
	stl    a,-8,*ar3+
	and    #255,a
	stl    a,*ar3+
	rptb   0x8447
	ldu    *ar2+%,a
	sftl   a,8
	or     a,-16
	stl    a,*ar3+
	ret
