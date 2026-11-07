; ROM6 0x9667 FRAG_9667 -- 27w, symbols.yaml data_word.
; Evidence: Bound 9667-9681 (exit F073@9680->283D objdump); 16 branch-join entries (13x F273 bd + 3x F073 b, no calls); interior bcd@9673->283D; shared pa54/port tail; abuts ROUTINE_9682; HYPO
; ORIGIN 0x9667
	.sect ".text"
	.mmregs
	.global _start
_start:
	nop
	portw  *ar2,54
	stl    a,*(0x20fc)
	ld     #0,a
	andm   #-65,*(0x20ff)
	bitf   *(0x20ff),#128
	bcd    0x283d,ntc
	stl    a,*(0x20fb)
	portr  12,*(0xb)
	or     *(0x3eca),b
	nop
	portw  *(0xb),12
	b      0x283d
