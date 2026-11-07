; ROM6 0x9C61 WRAP_9C61 -- 46w, symbols.yaml data_word.
; Evidence: Entry 4916 F77F F310 0001 8912 E800; bound 9C61-9C8E (exit FE00@9C8C + slots to 9C8E); callers F074@9B02 + F274@9C37 (objdump-verified); interior call F074 9C8F@9C89 (raw+objdump v
; ORIGIN 0x9C61
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar6,b
	sfta   b,-1
	sub    #1,b
	stlm   b,brc
	ld     #0,a
	or     #-1,a
	bc     0x9c82,blt
	rptbd  0x9c81
	ld     *ar2,-8,b
	xor    a,b
	and    #255,b
	add    #-8620,b
	stlm   b,ar4
	sftl   a,-8
	ld     *ar2+,b
	xor    *ar4,a
	xor    a,b
	and    #255,b
	add    #-8620,b
	stlm   b,ar4
	sftl   a,-8
	ld     *ar2,-8,b
	xor    *ar4,a
	bitf   *(0x16),#1
	bc     0x9c8b,ntc
	ld     *ar2,-8,b
	call   0x9c8f
	cmpl   a
	retd
	and    #-1,a
