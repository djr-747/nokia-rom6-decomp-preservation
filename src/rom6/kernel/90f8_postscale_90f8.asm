; ROM6 0x90F8 POSTSCALE_90F8 -- 32w, symbols.yaml data_word.
; Evidence: Entry 4A17 7717 3120; BOUND CORRECTED entry-linear: straight-line to first exit retd @0x9115, bound 90F8-9117 (incl delay); was 9145 (overclaim; tail 9118-9145 belongs to BUTTERFLY
; Wave-12: 90f7-twin head-dup (90F8-9107) removed with that file; 90e7 now ends at ret @90F7 abutting here.
; ORIGIN 0x90F8
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @90F8 4a17 pshm   ar7
	pshm   ar7
	; @90F9 7717 stm    #12576,ar7
	stm    #12576,ar7
	; @90FB 7712 stm    #3,ar2
	stm    #3,ar2
	; @90FD 771a stm    #7,brc
	stm    #7,brc
	; @90FF f072 rptb   0x9110
	rptb   0x9110
	; @9101 3097 ld     *ar7+,t
	ld     *ar7+,t
	; @9102 5a85 dadst  *ar5,a
	dadst  *ar5,a
	; @9103 5fd5 dsadt  *ar5+%,b
	dsadt  *ar5+%,b
	; @9104 8ed4 cmps   a,*ar4+%
	cmps   a,*ar4+%
	; @9105 8fd3 cmps   b,*ar3+%
	cmps   b,*ar3+%
	; @9106 4008 sub    0x08,16,a
	sub    0x08,16,a
	; @9107 430b sub    0x0b,16,b
	sub    0x0b,16,b
	; @9108 f465 sfta   a,5
	sfta   a,5
	; @9109 f483 sat    a
	sat    a
	; @910A f063 and    #-256,16,a
	and    #-256,16,a
	; @910C f765 sfta   b,5
	sfta   b,5
	; @910D f583 sat    b
	sat    b
	; @910E f3f8 sftl   b,-8
	sftl   b,-8
	; @910F f2a0 or     b,a
	or     b,a
	; @9110 8291 sth    a,*ar1+
	sth    a,*ar1+
	; @9111 8d96 st     trn,*ar6+
	st     trn,*ar6+
	; @9112 6c8a banz   0x90fd,*ar2-
	banz   0x90fd,*ar2-
	; @9114 8a17 popm   ar7
	popm   ar7
	; @9115 fe00 retd
	retd
	; @9116 6ddc mar    *ar4+0%
	mar    *ar4+0%
	; @9117 6ddb mar    *ar3+0%
	mar    *ar3+0%
