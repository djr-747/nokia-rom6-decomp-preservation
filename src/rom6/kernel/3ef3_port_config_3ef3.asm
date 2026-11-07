; ROM6 0x3EF3 PORT_CONFIG_3EF3 -- 209w, program_word (new, wave-19bx).
; Evidence: Post-RET head after FC00@3EF2 (no static xrefs; only data read is sub *(0x3EF3),a@A40A reading the first word as data); bound 3EF3-3FC3 (exit RET FC00@3FC3 byte-verified); interior bc F830@3F7B->3FC4 exterior; 4x call F074 4007 + call F074 3FFA verified; port-write ladder 2/14/15/4/9/5/7/10/47/13/11/8/0/1/32/33/42/48/3/43/37/38/17.
; ORIGIN 0x3EF3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x640
	ssbx   st1,intm
	stm    #96,ar2
	portr  2,*ar2
	andm   #-25,*ar2
	orm    #6148,*ar2
	nop
	portw  *ar2,2
	st     #4999,*ar2
	nop
	portw  *ar2,14
	rpt    #18
	nop
	mvdk   *ar2,0x36a
	st     #15000,*ar2
	nop
	portw  *ar2,15
	rpt    #22
	nop
	nop
	portw  *ar2,4
	rpt    #22
	nop
	nop
	portw  *ar2,9
	rpt    #22
	nop
	nop
	portw  *ar2,5
	rpt    #22
	nop
	nop
	portw  *ar2,7
	rpt    #22
	nop
	nop
	portw  *ar2,10
	rpt    #22
	nop
	nop
	portw  *ar2,47
	rpt    #20
	nop
	st     #0,*ar2
	nop
	portw  *ar2,13
	rpt    #22
	nop
	nop
	portw  *ar2,11
	rpt    #22
	nop
	nop
	portw  *ar2,8
	rpt    #22
	nop
	portr  0,*ar2
	orm    #13,*ar2
	andm   #-481,*ar2
	nop
	portw  *ar2,0
	rpt    #20
	nop
	st     #-1796,*ar2
	nop
	portw  *ar2,1
	rpt    #19
	nop
	rsbx   st1,intm
	st     #0,*ar2
	nop
	portw  *ar2,32
	st     #1154,*ar2+
	st     #5250,*ar2
	nop
	portw  *ar2,33
	nop
	nop
	portw  *ar2-,33
	nop
	nop
	portw  *ar2,33
	stm    #16017,ar3
	nop
	portw  *ar3,42
	st     #187,*ar2
	nop
	portw  *ar2,48
	st     #0,*ar2
	nop
	portw  *ar2,3
	rpt    #14
	nop
	bitf   *(0x3ec8),#32
	bc     0x3fc4,tc
	cmpm   *(0x3e7e),#2
	ld     *(0x3eb5),a
	and    #1024,a
	st     #680,*ar2
	xc     2,tc
	st     #640,*ar2
	xc     2,aneq
	st     #1696,*ar2
	nop
	portw  *ar2,43
	ld     *ar2,a
	ld     #11,b
	bitf   *(0x3eb5),#1024
	nop
	nop
	xc     2,tc
	ld     #1696,a
	call   0x4007
	ld     #0,a
	ld     #13,b
	call   0x4007
	ld     #0,a
	ld     #14,b
	call   0x4007
	ld     #512,a
	ld     #3,b
	call   0x4007
	stm    #16014,ar3
	nop
	portw  *ar3,37
	stm    #16015,ar3
	nop
	portw  *ar3,38
	st     #510,*ar2
	nop
	portw  *ar2,17
	rpt    #16
	nop
	ld     #0,a
	ld     #0,b
	call   0x4007
	ld     #1,16,a
	stm    #0,al
	call   0x3ffa
	ret
