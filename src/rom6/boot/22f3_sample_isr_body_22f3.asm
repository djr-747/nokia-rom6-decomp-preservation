; ROM6 0x22F3 SAMPLE_ISR_BODY_22F3 -- 765w, symbols.yaml program_word.
; Evidence: Entries 0x22F3 (SAMPLE head, fallthrough from the abutting 22F1 slot) + 0x25DF (V20 vector FFD2, STATE prologue flowing to 25F0/25F2); RX signal processing per roms/rom6/ivt.md (pa33 handshake, dispatch *(0x22C) 1->2468/2->257D, dual-MAC FIR BRC=7 coeffs AR5=0x3EBD, SQDST/DST Viterbi metrics, call-05DC, BCD loop *(0x22F)); epilogue pa33 + full popm + FRETE@25D8 (non-delayed exact 0xF4E5); dead lane 25D9-25DE (stm/rptz/stl + ret, unreachable post-FRETE, dark); externals 05Dx/06xx RAM-resident (zeros in-mask) + asm-only 3CD2/3E53/B634-gap + bound C851/3EE1/4315.
; ORIGIN 0x22F3
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    st1,a ; @0x22F3 4807
	and    #8192,a ; @0x22F4 f030
	or     #18688,a ; @0x22F6 f040
	stlm   a,st1 ; @0x22F8 8807
	portr  33,*(0x8) ; @0x22F9 74f8
	or     #3072,a ; @0x22FC f040
	mvdm   0x22a,ar2 ; @0x22FE 7212
	portw  *(0x8),33 ; @0x2300 75f8
	stm    #542,ar3 ; @0x2303 7713
	banz   0x2439,*ar2- ; @0x2305 6c8a
	stm    #556,ar2 ; @0x2307 7712
	cmpm   *ar2,#1 ; @0x2309 6082
	bc     0x2468,tc ; @0x230B f830
	cmpm   *ar2,#2 ; @0x230D 6082
	bc     0x257d,tc ; @0x230F f830
	stm    #552,ar1 ; @0x2311 7711
	stm    #16,bk ; @0x2313 7719
	ld     #0,asm ; @0x2315 ed00
	stm    #16061,ar5 ; @0x2316 7715
	stm    #2,ar0 ; @0x2318 7710
	stm    #512,ar6 ; @0x231A 7716
	stm    #516,ar4 ; @0x231C 7714
	stm    #7,brc ; @0x231E 771a
	rptbd  0x2343 ; @0x2320 f272
	stm    #500,ar2 ; @0x2322 7712
	portr  39,*ar6+% ; @0x2324 74d6
	mpy    *ar5,*ar4+,a ; @0x2326 a43a
	mpy    *ar5+,*ar4+0%,b ; @0x2327 a5be
	mac    *ar5,*ar4-,b ; @0x2328 b336
	mac    *ar5+,*ar4+0%,a ; @0x2329 b0be
	portr  39,*ar6+% ; @0x232A 74d6
	mac    *ar5,*ar4+,a ; @0x232C b03a
	mac    *ar5+,*ar4+0%,b ; @0x232D b3be
	mac    *ar5,*ar4-,b ; @0x232E b336
	mac    *ar5+,*ar4+0%,a ; @0x232F b0be
	portr  39,*ar6+% ; @0x2330 74d6
	mac    *ar5,*ar4+,a ; @0x2332 b03a
	mac    *ar5+,*ar4+0%,b ; @0x2333 b3be
	mac    *ar5,*ar4-,b ; @0x2334 b336
	mac    *ar5+,*ar4+0%,a ; @0x2335 b0be
	portr  39,*ar6+% ; @0x2336 74d6
	mac    *ar5,*ar4+,a ; @0x2338 b03a
	mac    *ar5+,*ar4+0%,b ; @0x2339 b3be
	macr   *ar5,*ar4-,b ; @0x233A b736
	st     b,*ar3 || macr   *ar4+0%,a ; @0x233B d6e1
	mar    *ar4+0% ; @0x233C 6ddc
	mar    *+ar5(0xfff9) ; @0x233D 6ded
	sub    *ar2+,16,a ; @0x233F 4092
	dld    *ar1,b ; @0x2340 5781
	sqdst  *ar3,*ar2 ; @0x2341 e210
	sqdst  *ar4+0%,*ar2- ; @0x2342 e2e4
	dst    b,*ar1 ; @0x2343 4f81
	call   0x5dc ; @0x2344 f074
	stm    #559,ar3 ; @0x2346 7713
	ld     #1,a ; @0x2348 e801
	sub    *ar3,a ; @0x2349 0883
	bcd    0x2437,aneq ; @0x234A fa44
	neg    a ; @0x234C f484
	stl    a,*ar3 ; @0x234D 8083
	stm    #556,ar3 ; @0x234E 7713
	bitf   *ar3,#8 ; @0x2350 6183
	bcd    0x242c,ntc ; @0x2352 fa20
	stm    #557,ar2 ; @0x2354 7712
	sfta   b,-3,a ; @0x2356 f67d
	call   0x4315 ; @0x2357 f074
	bitf   *(0x3ec8),#32 ; @0x2359 61f8
	bc     0x23f2,ntc ; @0x235C f820
	stm    #16024,ar2 ; @0x235E 7712
	neg    b ; @0x2360 f784
	add    *ar2,16,b ; @0x2361 3f82
	bitf   *(0x263b),#4 ; @0x2362 61f8
	stm    #1140,ar3 ; @0x2365 7713
	xc     2,ntc ; @0x2367 ff20
	stm    #1180,ar3 ; @0x2368 7713
	sub    *ar3(0x3),16,b,a ; @0x236A 42e3
	bcd    0x238f,aleq ; @0x236C fa47
	ld     #1,a ; @0x236E e801
	nop ; @0x236F f495
	sub    *ar3(0x4),16,b,a ; @0x2370 42e3
	bcd    0x238f,aleq ; @0x2372 fa47
	ld     #3,a ; @0x2374 e803
	nop ; @0x2375 f495
	sub    *ar3(0x5),16,b,a ; @0x2376 42e3
	bcd    0x238f,aleq ; @0x2378 fa47
	ld     #4,a ; @0x237A e804
	nop ; @0x237B f495
	sub    *ar3(0x6),16,b,a ; @0x237C 42e3
	bcd    0x238f,aleq ; @0x237E fa47
	ld     #5,a ; @0x2380 e805
	nop ; @0x2381 f495
	sub    *ar3(0x7),16,b,a ; @0x2382 42e3
	bcd    0x238f,aleq ; @0x2384 fa47
	ld     #6,a ; @0x2386 e806
	nop ; @0x2387 f495
	sub    *ar3(0x8),16,b,a ; @0x2388 42e3
	bcd    0x238f,aleq ; @0x238A fa47
	ld     #7,a ; @0x238C e807
	nop ; @0x238D f495
	ld     #8,a ; @0x238E e808
	stl    a,*(0x22d) ; @0x238F 80f8
	add    #16106,a ; @0x2391 f000
	stlm   a,ar3 ; @0x2393 8813
	nop ; @0x2394 f495
	nop ; @0x2395 f495
	ld     *ar3,a ; @0x2396 1083
	cmpm   *(0x22c),#9 ; @0x2397 60f8
	bc     0x239e,ntc ; @0x239A f820
	and    #-2,a ; @0x239C f030
	stm    #4726,ar3 ; @0x239E 7713
	and    #32,a,b ; @0x23A0 f130
	bcd    0x23a9,beq ; @0x23A2 fa4d
	and    #-32768,a,b ; @0x23A4 f130
	ld     a,b ; @0x23A6 f540
	b      0x23ab ; @0x23A7 f073
	or     #31,b ; @0x23A9 f340
	and    #-2,b ; @0x23AB f330
	stl    b,*ar3+ ; @0x23AD 8193
	st     #18048,*ar3+ ; @0x23AE 7693
	stl    a,*ar3+ ; @0x23B0 8093
	st     #18048,*ar3+ ; @0x23B1 7693
	stm    #4723,ar3 ; @0x23B3 7713
	ld     *ar3-,b ; @0x23B5 118b
	add    #192,b ; @0x23B6 f300
	sub    *(0x36a),b,a ; @0x23B8 6ff8
	nop ; @0x23BB f495
	nop ; @0x23BC f495
	.word 0xFD43 ; XC gas encoder gap (xc     1,alt)
	ld     b,a ; @0x23BE f640
	or     #256,16,a ; @0x23BF f064
	dst    a,*ar3 ; @0x23C1 4e83
	call   0x3ee1 ; @0x23C2 f074
	add    *(0x3ee7),a ; @0x23C4 00f8
	sub    *(0x36a),a,b ; @0x23C6 6ff8
	nop ; @0x23C9 f495
	nop ; @0x23CA f495
	.word 0xFD4B ; XC gas encoder gap (xc     1,blt)
	ld     a,b ; @0x23CC f540
	stl    b,*(0x1271) ; @0x23CD 81f8
	orm    #4096,*(0x13d0) ; @0x23CF 69f8
	stm    #4726,ar3 ; @0x23D2 7713
	stm    #4720,ar2 ; @0x23D4 7712
	nop ; @0x23D6 f495
	portw  *ar2+,48 ; @0x23D7 7592
	nop ; @0x23D9 f495
	nop ; @0x23DA f495
	portw  *ar3+,49 ; @0x23DB 7593
	nop ; @0x23DD f495
	nop ; @0x23DE f495
	portw  *ar3+,50 ; @0x23DF 7593
	nop ; @0x23E1 f495
	nop ; @0x23E2 f495
	portw  *ar2,4 ; @0x23E3 7582
	rpt    #14 ; @0x23E5 ec0e
	nop ; @0x23E6 f495
	mvdk   *ar2+,0x58e ; @0x23E7 7192
	stm    #552,ar2 ; @0x23E9 7712
	ld     #0,a ; @0x23EB e800
	dst    a,*ar2+ ; @0x23EC 4e92
	st     #5,*(0x22a) ; @0x23ED 76f8
	b      0x2427 ; @0x23F0 f073
	sfta   b,-6 ; @0x23F2 f77a
	stm    #21845,t ; @0x23F3 770e
	mpyr   *(0xc),a ; @0x23F5 22f8
	sfta   a,1,b ; @0x23F7 f561
	add    a,b ; @0x23F8 f500
	bitf   *(0x51d),#16 ; @0x23F9 61f8
	stm    #16024,ar2 ; @0x23FC 7712
	.word 0xFD20 ; XC gas encoder gap (xc     1,ntc)
	mar    *ar2+ ; @0x23FF 6d92
	neg    b,a ; @0x2400 f684
	add    *ar2,16,a ; @0x2401 3c82
	ld     #0,b ; @0x2402 e900
	max    a ; @0x2403 f486
	ld     *(0x3e94),16,b ; @0x2404 45f8
	bitf   *(0x51f),#128 ; @0x2406 61f8
	bc     0x2412,ntc ; @0x2409 f820
	bitf   *(0x263b),#4 ; @0x240B 61f8
	bc     0x2412,tc ; @0x240E f830
	ld     *(0x3edc),16,b ; @0x2410 45f8
	min    a ; @0x2412 f487
	calld  0x3cd2 ; @0x2413 f274
	sth    a,*(0x22d) ; @0x2415 82f8
	ld     #0,a ; @0x2417 e800
	dst    a,*(0x228) ; @0x2418 4ef8
	stm    #1309,ar2 ; @0x241A 7712
	bitf   *ar2,#16 ; @0x241C 6182
	st     #2,*(0x22a) ; @0x241E 76f8
	bc     0x2427,ntc ; @0x2421 f820
	bd     0x2437 ; @0x2423 f273
	andm   #-17,*ar2 ; @0x2425 6882
	andm   #-9,*(0x22c) ; @0x2427 68f8
	b      0x2437 ; @0x242A f073
	sfta   b,-5,a ; @0x242C f67b
	call   0x4315 ; @0x242D f074
	stm    #555,ar2 ; @0x242F 7712
	sth    b,*ar2- ; @0x2431 838a
	orm    #1,*(0x51d) ; @0x2432 69f8
	call   0x3e53 ; @0x2435 f074
	b      0x25bc ; @0x2437 f073
	stm    #16,bk ; @0x2439 7719
	stm    #7,brc ; @0x243B 771a
	rptbd  0x244c ; @0x243D f272
	stm    #512,ar4 ; @0x243F 7714
	portr  39,*ar4+% ; @0x2441 74d4
	nop ; @0x2443 f495
	portr  39,*ar4+% ; @0x2444 74d4
	nop ; @0x2446 f495
	portr  39,*ar4+% ; @0x2447 74d4
	nop ; @0x2449 f495
	portr  39,*ar4+% ; @0x244A 74d4
	nop ; @0x244C f495
	banzd  0x25bc,*ar2 ; @0x244D 6e82
	mvmd   ar2,0x22a ; @0x244F 7312
	stm    #556,ar2 ; @0x2451 7712
	bitf   *ar2,#8 ; @0x2453 6182
	bc     0x245a,ntc ; @0x2455 f820
	ld     #1,b ; @0x2457 e901
	b      0x2464 ; @0x2458 f073
	cmpm   *ar2,#2 ; @0x245A 6082
	bc     0x2462,ntc ; @0x245C f820
	bd     0x2464 ; @0x245E f273
	mvdm   0x230,bl ; @0x2460 720b
	mvdm   0x22e,bl ; @0x2462 720b
	bd     0x25bc ; @0x2464 f273
	mvmd   bl,0x22f ; @0x2466 730b
	call   0x5de ; @0x2468 f074
	pshm   *(0x60) ; @0x246A 4a60
	pshm   *(0x61) ; @0x246B 4a61
	stm    #200,ar2 ; @0x246C 7712
	mvmm   ar2,ar3 ; @0x246E e723
	stm    #16,bk ; @0x246F 7719
	ld     #0,asm ; @0x2471 ed00
	stm    #16061,ar5 ; @0x2472 7715
	stm    #2,ar0 ; @0x2474 7710
	stm    #512,ar6 ; @0x2476 7716
	stm    #7,brc ; @0x2478 771a
	rptbd  0x2499 ; @0x247A f272
	stm    #516,ar4 ; @0x247C 7714
	portr  39,*ar6+% ; @0x247E 74d6
	mpy    *ar5,*ar4+,a ; @0x2480 a43a
	mpy    *ar5+,*ar4+0%,b ; @0x2481 a5be
	mac    *ar5,*ar4-,b ; @0x2482 b336
	mac    *ar5+,*ar4+0%,a ; @0x2483 b0be
	portr  39,*ar6+% ; @0x2484 74d6
	mac    *ar5,*ar4+,a ; @0x2486 b03a
	mac    *ar5+,*ar4+0%,b ; @0x2487 b3be
	mac    *ar5,*ar4-,b ; @0x2488 b336
	mac    *ar5+,*ar4+0%,a ; @0x2489 b0be
	portr  39,*ar6+% ; @0x248A 74d6
	mac    *ar5,*ar4+,a ; @0x248C b03a
	mac    *ar5+,*ar4+0%,b ; @0x248D b3be
	mac    *ar5,*ar4-,b ; @0x248E b336
	mac    *ar5+,*ar4+0%,a ; @0x248F b0be
	portr  39,*ar6+% ; @0x2490 74d6
	mac    *ar5,*ar4+,a ; @0x2492 b03a
	mac    *ar5+,*ar4+0%,b ; @0x2493 b3be
	macr   *ar5,*ar4-,b ; @0x2494 b736
	st     b,*ar3+ || macr   *ar4+0%,a ; @0x2495 d6e9
	st     a,*ar3+ || ld     *ar4+0%,t ; @0x2496 e4e9
	mar    *ar4+0% ; @0x2497 6ddc
	mar    *+ar5(0xfff9) ; @0x2498 6ded
	cmpm   *(0x56e),#1 ; @0x249A 60f8
	bc     0x24bb,tc ; @0x249D f830
	ld     *ar2+,16,b ; @0x249F 4592
	ld     *ar2+,16,a ; @0x24A0 4492
	add    *ar2+,16,a ; @0x24A1 3c92
	sub    *ar2+,16,b ; @0x24A2 4392
	sub    *ar2+,16,b ; @0x24A3 4392
	sub    *ar2+,16,a ; @0x24A4 4092
	sub    *ar2+,16,a ; @0x24A5 4092
	stm    #72,bk ; @0x24A6 7719
	mvdm   0x518,ar3 ; @0x24A8 7213
	add    *ar2+,16,b ; @0x24AA 3f92
	sth    a,*ar3+% ; @0x24AB 82d3
	sth    b,*ar3+% ; @0x24AC 83d3
	ld     *ar2+,16,b ; @0x24AD 4592
	ld     *ar2+,16,a ; @0x24AE 4492
	add    *ar2+,16,a ; @0x24AF 3c92
	sub    *ar2+,16,b ; @0x24B0 4392
	sub    *ar2+,16,b ; @0x24B1 4392
	sub    *ar2+,16,a ; @0x24B2 4092
	sub    *ar2+,16,a ; @0x24B3 4092
	add    *ar2,16,b ; @0x24B4 3f82
	sth    a,*ar3+% ; @0x24B5 82d3
	sth    b,*ar3+% ; @0x24B6 83d3
	bd     0x24d4 ; @0x24B7 f273
	mvmd   ar3,0x518 ; @0x24B9 7313
	ld     *ar2+,16,b ; @0x24BB 4592
	ld     *ar2+,16,a ; @0x24BC 4492
	add    *ar2+,16,a ; @0x24BD 3c92
	sub    *ar2+,16,b ; @0x24BE 4392
	sub    *ar2+,16,b ; @0x24BF 4392
	sub    *ar2+,16,a ; @0x24C0 4092
	sub    *ar2+,16,a ; @0x24C1 4092
	add    *ar2+,16,b ; @0x24C2 3f92
	add    *ar2+,16,b ; @0x24C3 3f92
	add    *ar2+,16,a ; @0x24C4 3c92
	add    *ar2+,16,a ; @0x24C5 3c92
	sub    *ar2+,16,b ; @0x24C6 4392
	sub    *ar2+,16,b ; @0x24C7 4392
	sub    *ar2+,16,a ; @0x24C8 4092
	sub    *ar2+,16,a ; @0x24C9 4092
	add    *ar2,16,b ; @0x24CA 3f82
	stm    #72,bk ; @0x24CB 7719
	mvdm   0x518,ar3 ; @0x24CD 7213
	nop ; @0x24CF f495
	sth    a,*ar3+% ; @0x24D0 82d3
	sth    b,*ar3+% ; @0x24D1 83d3
	mvmd   ar3,0x518 ; @0x24D2 7313
	call   0x5e0 ; @0x24D4 f074
	stm    #500,ar3 ; @0x24D6 7713
	stm    #3,brc ; @0x24D8 771a
	rptbd  0x24df ; @0x24DA f272
	ld     #0,b ; @0x24DC e900
	sub    *ar2-,*ar3+,a ; @0x24DD a249
	sqdst  *ar2-,*ar3- ; @0x24DE e245
	sqdst  *ar2-,*ar3+ ; @0x24DF e249
	call   0x5e2 ; @0x24E0 f074
	stm    #72,bk ; @0x24E2 7719
	mvdm   0x51a,ar2 ; @0x24E4 7212
	nop ; @0x24E6 f495
	dst    b,*ar2+% ; @0x24E7 4fd2
	mvmd   ar2,0x51a ; @0x24E8 7312
	stm    #1309,ar3 ; @0x24EA 7713
	bitf   *ar3,#2 ; @0x24EC 6183
	bcd    0x2547,tc ; @0x24EE fa30
	andm   #-3,*ar3 ; @0x24F0 6883
	orm    #2,*ar3 ; @0x24F2 6983
	bitf   *(0x3ec8),#32 ; @0x24F4 61f8
	ld     *(0x55f),a ; @0x24F7 10f8
	bc     0x24fd,ntc ; @0x24F9 f820
	bc     0x2547,aneq ; @0x24FB f844
	stm    #96,ar3 ; @0x24FD 7713
	dld    *(0x3eaa),a ; @0x24FF 56f8
	sub    b,a ; @0x2501 f620
	bcd    0x252b,alt ; @0x2502 fa43
	stm    #557,ar2 ; @0x2504 7712
	bc     0x2513,ntc ; @0x2506 f820
	ld     *ar2,a ; @0x2508 1082
	add    #1,a ; @0x2509 f000
	ld     #8,b ; @0x250B e908
	min    a ; @0x250C f487
	sub    *ar2,a,b ; @0x250D 6f82
	bc     0x2547,beq ; @0x250F f84d
	b      0x254b ; @0x2511 f073
	mvkd   0x3e94,*ar3 ; @0x2513 7083
	bitf   *(0x51f),#128 ; @0x2515 61f8
	bc     0x2521,ntc ; @0x2518 f820
	bitf   *(0x263b),#4 ; @0x251A 61f8
	bc     0x2521,tc ; @0x251D f830
	mvkd   0x3edc,*ar3 ; @0x251F 7083
	sub    *ar2,*ar3,a ; @0x2521 a201
	bc     0x2547,aeq ; @0x2522 f845
	ld     #6,16,a ; @0x2524 f062
	add    *ar2,16,a ; @0x2526 3c82
	bd     0x2543 ; @0x2527 f273
	ld     *ar3,16,b ; @0x2529 4583
	min    a ; @0x252A f487
	dld    *(0x3ea8),a ; @0x252B 56f8
	sub    b,a ; @0x252D f620
	bc     0x2547,agt ; @0x252E f846
	bc     0x253d,ntc ; @0x2530 f820
	ld     *ar2,a ; @0x2532 1082
	sub    #1,a ; @0x2533 f010
	ld     #0,b ; @0x2535 e900
	max    a ; @0x2536 f486
	sub    *ar2,a,b ; @0x2537 6f82
	bc     0x2547,beq ; @0x2539 f84d
	b      0x254b ; @0x253B f073
	ld     #3,16,a ; @0x253D f062
	sub    *ar2,16,a ; @0x253F 4082
	neg    a ; @0x2540 f484
	bc     0x2547,alt ; @0x2541 f843
	calld  0x3cd2 ; @0x2543 f274
	sth    a,*(0x22d) ; @0x2545 82f8
	bd     0x25bc ; @0x2547 f273
	popm   *(0x61) ; @0x2549 8a61
	popm   *(0x60) ; @0x254A 8a60
	stl    a,*(0x22d) ; @0x254B 80f8
	add    #16106,a ; @0x254D f000
	stlm   a,ar3 ; @0x254F 8813
	nop ; @0x2550 f495
	nop ; @0x2551 f495
	ld     *ar3,16,a ; @0x2552 4483
	and    #-2,16,a ; @0x2553 f063
	stm    #18048,al ; @0x2555 7708
	ld     #256,b ; @0x2557 f120
	nop ; @0x2559 f495
	portw  *(0x9),49 ; @0x255A 75f8
	nop ; @0x255D f495
	nop ; @0x255E f495
	portw  *(0x8),50 ; @0x255F 75f8
	nop ; @0x2562 f495
	nop ; @0x2563 f495
	portw  *(0xb),48 ; @0x2564 75f8
	nop ; @0x2567 f495
	call   0x3ee1 ; @0x2568 f074
	add    *(0x3ee7),a ; @0x256A 00f8
	sub    *(0x36a),a,b ; @0x256C 6ff8
	bc     0x2572,blt ; @0x256F f84b
	ld     b,a ; @0x2571 f640
	nop ; @0x2572 f495
	portw  *(0x8),4 ; @0x2573 75f8
	rpt    #14 ; @0x2576 ec0e
	nop ; @0x2577 f495
	orm    #16,*(0x13d0) ; @0x2578 69f8
	b      0x2547 ; @0x257B f073
	call   0x5e4 ; @0x257D f074
	mvdm   0x231,ar3 ; @0x257F 7213
	stm    #16,bk ; @0x2581 7719
	stm    #16061,ar5 ; @0x2583 7715
	stm    #2,ar0 ; @0x2585 7710
	ld     #0,asm ; @0x2587 ed00
	stm    #516,ar4 ; @0x2588 7714
	stm    #512,ar6 ; @0x258A 7716
	stm    #7,brc ; @0x258C 771a
	rptbd  0x25af ; @0x258E f272
	stm    #500,ar2 ; @0x2590 7712
	portr  39,*ar6+% ; @0x2592 74d6
	mpy    *ar5,*ar4+,a ; @0x2594 a43a
	mpy    *ar5+,*ar4+0%,b ; @0x2595 a5be
	mac    *ar5,*ar4-,b ; @0x2596 b336
	mac    *ar5+,*ar4+0%,a ; @0x2597 b0be
	portr  39,*ar6+% ; @0x2598 74d6
	mac    *ar5,*ar4+,a ; @0x259A b03a
	mac    *ar5+,*ar4+0%,b ; @0x259B b3be
	mac    *ar5,*ar4-,b ; @0x259C b336
	mac    *ar5+,*ar4+0%,a ; @0x259D b0be
	portr  39,*ar6+% ; @0x259E 74d6
	mac    *ar5,*ar4+,a ; @0x25A0 b03a
	mac    *ar5+,*ar4+0%,b ; @0x25A1 b3be
	mac    *ar5,*ar4-,b ; @0x25A2 b336
	mac    *ar5+,*ar4+0%,a ; @0x25A3 b0be
	portr  39,*ar6+% ; @0x25A4 74d6
	mac    *ar5,*ar4+,a ; @0x25A6 b03a
	mac    *ar5+,*ar4+0%,b ; @0x25A7 b3be
	macr   *ar5,*ar4-,b ; @0x25A8 b736
	macr   *ar5,*ar4+0%,a ; @0x25A9 b43e
	mar    *+ar5(0xfff9) ; @0x25AA 6ded
	sub    *ar2+,16,a ; @0x25AC 4092
	st     a,*ar3+ || ld     *ar4+0%,t ; @0x25AD e4e9
	sub    *ar2-,16,b ; @0x25AE 438a
	st     b,*ar3+ || ld     *ar4+0%,t ; @0x25AF e6e9
	call   0x5e6 ; @0x25B0 f074
	mvmd   ar3,0x231 ; @0x25B2 7313
	stm    #559,ar2 ; @0x25B4 7712
	ld     *ar2,a ; @0x25B6 1082
	sub    #1,a ; @0x25B7 f010
	stl    a,*ar2 ; @0x25B9 8082
	cc     0x3e53,aeq ; @0x25BA f945
	portr  33,*(0x8) ; @0x25BC 74f8
	and    #-2049,a ; @0x25BF f030
	popm   bk ; @0x25C1 8a19
	popm   rea ; @0x25C2 8a1c
	portw  *(0x8),33 ; @0x25C3 75f8
	popm   rsa ; @0x25C6 8a1b
	popm   brc ; @0x25C7 8a1a
	popm   ar3 ; @0x25C8 8a13
	popm   ar2 ; @0x25C9 8a12
	popm   ar5 ; @0x25CA 8a15
	popm   ar4 ; @0x25CB 8a14
	popm   ar0 ; @0x25CC 8a10
	popm   ar6 ; @0x25CD 8a16
	popm   ar1 ; @0x25CE 8a11
	popm   t ; @0x25CF 8a0e
	popm   bg ; @0x25D0 8a0d
	popm   bh ; @0x25D1 8a0c
	popm   bl ; @0x25D2 8a0b
	popm   ag ; @0x25D3 8a0a
	popm   ah ; @0x25D4 8a09
	popm   al ; @0x25D5 8a08
	popm   st1 ; @0x25D6 8a07
	popm   st0 ; @0x25D7 8a06
	frete ; @0x25D8 f4e5
	stm    #512,ar4 ; @0x25D9 7714
	rptz   a,#15 ; @0x25DB f071
	stl    a,*ar4+ ; @0x25DD 8094
	ret ; @0x25DE fc00
	call   0x5e8 ; @0x25DF f074
	pshm   st1 ; @0x25E1 4a07
	pshm   al ; @0x25E2 4a08
	pshm   ah ; @0x25E3 4a09
	pshm   ag ; @0x25E4 4a0a
	pshm   bl ; @0x25E5 4a0b
	pshm   bh ; @0x25E6 4a0c
	pshm   bg ; @0x25E7 4a0d
	pshm   t ; @0x25E8 4a0e
	pshm   ar2 ; @0x25E9 4a12
	pshm   ar3 ; @0x25EA 4a13
	pshm   bk ; @0x25EB 4a19
	pshm   rsa ; @0x25EC 4a1b
	pshm   rea ; @0x25ED 4a1c
	stm    #0,rsa ; @0x25EE 771b
