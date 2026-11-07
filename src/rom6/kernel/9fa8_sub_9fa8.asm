; ROM6 0x9FA8 SUB_9FA8 -- 39w, symbols.yaml data_word.
; Evidence: Bound 9FA8-9FCE (39w; exit RET FC00@9FCE byte-verified); entry F074 0616; 7 callers F074 @0x53C9/0x53E3/0x541A/0x542C/0x5483/0x549C/0xC8AE (C8AE byte-verified, rest team objdump); 
; ORIGIN 0x9FA8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x616
	stm    #572,ar3
	ld     #0,a
	dst    a,*ar3
	stl    a,*(0x23f)
	dst    a,*(0x238)
	ld     #25305,2,a
	dst    a,*(0x23a)
	st     #1,*(0x23e)
	dld    *(0x288a),b
	dst    b,*(0x288e)
	ld     #0,b
	stl    b,*(0x2893)
	stl    b,*(0x2894)
	stl    b,*(0x2895)
	stl    b,*(0x2896)
	ld     *(0x8e6),a
	and    #255,a
	stl    a,*(0x2898)
	stl    a,*(0x2897)
	ret
