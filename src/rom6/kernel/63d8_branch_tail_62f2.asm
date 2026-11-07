; ROM6 0x63D8 BRANCH_TAIL_62F2 -- 2w, symbols.yaml data_word.
; Evidence: Entry 60F8 2614 0003 CMPM *(0x2614),#3 + F830 62F9 + F073 6320; 7 bc refs (0x62A2/0x62A6/0x62CB/0x62CF/0x62E0/0x62E3/0x62EC), zero true CALLs; cluster CALLs 0x63DA via F074 @0x634F
; ORIGIN 0x63D8
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar7+
	stl    a,*ar7
