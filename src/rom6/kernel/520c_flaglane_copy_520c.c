/* ROM6 ORIGIN 0x520C (118w): FLAGLANE_COPY_520C -- flag lanes plus block copies.
 * Verified encoding: src/rom6/kernel/520c_flaglane_copy_520c.asm (recombine MATCH).
 * ORIGIN 0x520C
 * EXPECT: F074 059C 7711 2628 6181 0001 FA20 5218 7712 2627 6882 DFFF 61F8 2512 0080 F820 5220 6181 0020 FC20 10F8 265C 1182 F845 5228 F340 2000 8182 F230 0010 FC45 F330 FFEF 8182 6981 0002 7712 263A 6882 FFFE 11F8 2639 F330 0001 1B82 8182 71F8 2655 2654 7712 25A1 7713 310A EC1F E589 7712 2494 7713 312A EC5F E589 7712 03D9 7713 318A EC1F E589 71F8 265C 31AA 61F8 3EC8 0010 F820 5263 7712 03B5 7713 25A1 EC1F E589 11F8 0588 81F8 265C F073 5273 7712 03D4 61F8 3EC8 0040 F495 F495 FF30 6DEA 0004 F274 434F 7713 25A1 81F8 265C 7712 2627 FE4D 6882 DFFF 6982 2000 61F8 263A 1000 F820 5282 F074 6F79 FC00
 *
 * Intent: Flag-lane setup, three block copies, conditional fourth copy,
 * 434F call, status-bit epilogue. Runs dark SUB_059C (opaque, forward
 * extern; A/B rewritten after, outputs dead). AR1 = 0x2628; BITF bit 0
 * plus bcd 0x5218,ntc under WORD-count delay slots (ti-c54x
 * delayed_branch oracle: 2-word consume fires at once, arm replaces
 * pending): the stm delay fills the window, so NTC-taken jumps to
 * 5218 SKIPPING the andm, while TC-fallthrough runs the andm at 5216
 * then rejoins (bcd-delay precedent per a7b7, corrected to the word
 * rule). Cell 0x2512 bit 7 clear chains to 5220 (bc ntc);
 * cell 0x2628 bit 5 clear returns (rc ntc, taken-return, oracle op_rc).
 * A = *0x265C; B = *0x2627; A == 0 chains to 5228, else B |= 8192 and
 * *0x2627 = B-low. A = B & 16 (AND B-destination, oracle
 * op_logical_immediate destination field; zero-extended immediate
 * clears guard, so the aeq test is low-32 exact); A == 0 returns
 * (rc aeq). B &= ~17, *0x2627 = B-low, cell 0x2628 |= 2 (orm),
 * AR2 = 0x263A, cell &= ~2 (andm), B = *0x2639 & 1, B |= *0x263A
 * (or Smem,B-destination, oracle op_or_smem), *0x263A = B-low.
 * *0x2654 = *0x2655 (mvdk decodes MVDK_SMEM 0x7180: Smem to dmad,
 * dest-second, catalog P3-S61). Three rpt+mvdd block copies
 * (RPT #k runs k+1, MVDD steps both ARs, dest writes low16 exact):
 * 32 words 0x25A1->0x310A, 96 words 0x2494->0x312A, 32 words
 * 0x03D9->0x318A. *0x31AA = *0x265C (mvdk). Cell 0x3EC8 bit 4 clear
 * chains to 5263 (bc ntc), else 32 words 0x03B5->0x25A1, B = *0x588,
 * *0x265C = B-low, jump to 5273. 5263: AR2 = 0x03D4; cell 0x3EC8
 * bit 6 set steps AR2 += 4 (xc 2,tc skips the 2-word mar when clear;
 * the calld runs either way). calld ROUTINE_434F (linked C; the stm
 * delay fills the window so the call fires first, and the stl sits at
 * the return address 5271 and runs on return: AR3 = 0x25A1,
 * *0x265C = B-low, with B carried from the 5238 OR-lane or the 0x588
 * load). 5273: AR2 = 0x2627; the rcd andm delay fills the window,
 * then B == 0 returns SKIPPING the orm, else the orm at 5278 runs
 * (word-count rule) and the tail continues. NOTE: B at the rcd is
 * 434F's B-out -- dark 436C residue in
 * HW; the C model preserves pre-call B (void externs touch no locals),
 * so the test follows the C-model value; divergence flagged. Cell
 * 0x263A bit 12 clear tail-calls DISPATCH_SLED_A (asm-only, forward
 * extern; sled writes A before reading it and never uses B, so the
 * jump loses no observable state; its AR6/AR7 derefs are a future-C
 * param gap, noted). Else runs LEAF_6F79_FILL (linked C, void) and
 * returns (ret, no delay). A/B live-outs: A = B&16 residue (concrete),
 * B = 434F B-out (dark, flagged). AR7 entry dark (never set in-span):
 * explicit ar7_in param passed to ROUTINE_434F. AR1-AR5/AR0 set or
 * untouched in-span; no other params. 40-bit exactness: every AND/OR
 * mask zero-extends to full 40 (oracle op_logical_immediate), clearing
 * guard/high, so all beq/aeq tests and stl stores are low-32 exact;
 * full-40 B == 0 coincides with long B == 0 (sign-extension preserves
 * zero both ways). BRC/T/OVM untouched.
 * Bound 520C-5281 (ret FC00@5281; abuts DISPATCH_SLED_A at 5282).
 * Entry call F074@51D8 (post-RET abut caller).
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void routine_434F(int ar7_live);
extern void leaf_6F79_fill(void);
extern void dispatch_sled_A(void); /* 5282_dispatch_sled_a; see docs/evidence/extern-triage.md */
void flaglane_copy_520C(int ar7_in)
{
    long a;
    long b;
    int *ar1;
    int *ar2;
    int *ar3;
    int i;

    sub_059C();                                            /* call 0x59c */
    ar1 = (int *)0x2628;                                  /* stm #9768,ar1 */
    ar2 = (int *)0x2627;                                  /* bcd delay (fills window) */
    if ((*ar1 & 1) == 0)                                  /* bcd taken: skips andm */
        goto lane_5218;
    *ar2 &= 0xDFFF;                                       /* fallthrough: andm runs */
lane_5218:                                                /* 5218 tune check */
    if ((*(volatile int *)0x2512 & 128) == 0)             /* bitf; bc ntc */
        goto lane_5220;
    if ((*ar1 & 32) == 0)                                 /* bitf; rc ntc */
        return;
lane_5220:                                                /* 5220 tune */
    a = (long)*(volatile int *)0x265C;                    /* ld *(0x265c),a */
    b = (long)*ar2;                                       /* ld *ar2,b */
    if (a == 0)                                           /* bc 0x5228,aeq */
        goto and_5228;
    b |= 8192L;                                           /* or #8192,b */
    *ar2 = (int)(b & 0xFFFF);                             /* stl b,*ar2 */
and_5228:                                                 /* 5228 and lane */
    a = b & 16L;                                          /* and #16,b,a */
    if (a == 0)                                           /* rc aeq */
        return;
    b &= 0xFFEFL;                                         /* and #-17,b */
    *ar2 = (int)(b & 0xFFFF);                             /* stl b,*ar2 */
    *ar1 |= 2;                                            /* orm #2,*ar1 */
    ar2 = (int *)0x263A;                                  /* stm #9786,ar2 */
    *(volatile int *)0x263A &= 0xFFFE;                    /* andm #-2,*ar2 */
    b = (long)*(volatile int *)0x2639;                    /* ld *(0x2639),b */
    b &= 1L;                                              /* and #1,b */
    b |= (long)*ar2;                                      /* or *ar2,b */
    *ar2 = (int)(b & 0xFFFF);                             /* stl b,*ar2 */
    *(volatile int *)0x2654 = *(volatile int *)0x2655;    /* mvdk */
    ar2 = (int *)0x25A1;                                  /* stm #9633,ar2 */
    ar3 = (int *)0x310A;                                  /* stm #12554,ar3 */
    for (i = 0; i < 32; i++)                              /* rpt #31 */
        *ar3++ = *ar2++;                                  /* mvdd */
    ar2 = (int *)0x2494;                                  /* stm #9364,ar2 */
    ar3 = (int *)0x312A;                                  /* stm #12586,ar3 */
    for (i = 0; i < 96; i++)                              /* rpt #95 */
        *ar3++ = *ar2++;                                  /* mvdd */
    ar2 = (int *)0x03D9;                                  /* stm #985,ar2 */
    ar3 = (int *)0x318A;                                  /* stm #12682,ar3 */
    for (i = 0; i < 32; i++)                              /* rpt #31 */
        *ar3++ = *ar2++;                                  /* mvdd */
    *(volatile int *)0x31AA = *(volatile int *)0x265C;    /* mvdk */
    if ((*(volatile int *)0x3EC8 & 16) == 0)              /* bitf; bc ntc */
        goto lane_5263;
    ar2 = (int *)0x03B5;                                  /* stm #949,ar2 */
    ar3 = (int *)0x25A1;                                  /* stm #9633,ar3 */
    for (i = 0; i < 32; i++)                              /* rpt #31 */
        *ar3++ = *ar2++;                                  /* mvdd */
    b = (long)*(volatile int *)0x0588;                    /* ld *(0x588),b */
    *(volatile int *)0x265C = (int)(b & 0xFFFF);          /* stl b,0x265c */
    goto join_5273;                                       /* b 0x5273 */
lane_5263:                                                /* 5263 alt copy */
    ar2 = (int *)0x03D4;                                  /* stm #980,ar2 */
    if ((*(volatile int *)0x3EC8 & 64) != 0)              /* bitf; xc 2,tc */
        ar2 += 4;                                         /* mar *+ar2(0x4) */
    /* calld 0x434f: stm delay fills the window, call fires, return
     * address 5271 runs the stl on return (word-count rule): */
    ar3 = (int *)0x25A1;                                  /* calld delay */
    routine_434F(ar7_in);                                 /* calld 0x434f */
    *(volatile int *)0x265C = (int)(b & 0xFFFF);          /* return-addr stl */
join_5273:                                                /* 5273 epilogue */
    ar2 = (int *)0x2627;                                  /* stm #9767,ar2 */
    *(volatile int *)0x2627 &= 0xDFFF;                    /* rcd delay (fills window) */
    if (b == 0)                                           /* rcd taken: orm skipped */
        return;
    *(volatile int *)0x2627 |= 0x2000;                    /* fallthrough: orm runs */
    if ((*(volatile int *)0x263A & 4096) == 0) {          /* bitf; bc ntc */
        dispatch_sled_A();                                /* tail (see note) */
        return;
    }
    leaf_6F79_fill();                                     /* call 0x6f79 */
    /* ret */
}
