; ROM6 0x8611 COPY14_8611 -- 13w, symbols.yaml data_word.
; Evidence: Entry 4A15 EC05 E58B 8A15 7712 04F5 4492 1A8A 4595 1B8D F1C0 8395 818D FC00; RET @861E len 14; 4 callers F074 @850C/8517/8522/852D; no inner calls; block-copy+accumulate; HYPOTHESI
; Wave-12: exit ret @861E owned here; pool bundle 861e_copy14_8611.asm split (ret belonged here; dld/call/dst stub 861F-8626 now 861f_stub_861f; rptb head 8627-862C owned by 8627).
; ORIGIN 0x8611
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar5
	rpt    #5
	mvdd   *ar2+,*ar5+
	popm   ar5
	stm    #1269,ar2
	ld     *ar2+,16,a
	or     *ar2-,a
	ld     *ar5+,16,b
	or     *ar5-,b
	xor    a,b
	sth    b,*ar5+
	stl    b,*ar5-
