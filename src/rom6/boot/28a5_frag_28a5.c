/* ROM6 0x28A5 FRAG_28A5 -- 42w.
 * Verified encoding: src/rom6/boot/28a5_frag_28a5.asm (recombine MATCH).
 * ORIGIN 0x28A5
 * EXPECT: F074 0732 7713 0542 7714 0546 A112 F3F0 8914 6B83 0001 1384 7714 0547 A012 F0F0 8814 F495 F495 1284 F074 0734 F495 75F8 0008 000F EC02 F495 1093 69F8 263A 0002 0883 F842 28CB 68F8 263A FFFD FF45 7683 0000 F5E2
 *
 * Intent: Boot cell-combine lane (name fixed by the 2875 forward
 * import: void frag_28A5(void)). Runs dark SUB_0732/SUB_0734 (no
 * symbols, opaque; cells 1346/1350/1351 may be callee-written,
 * re-read volatile after each call -- flagged). AR3 = 1346,
 * AR4 = 1350 locals (stm-created, reseated, not carried). B =
 * MEM[1346] + MEM[1350] (add dual); B >>= 16 logical (sftl b,-16:
 * unsigned-long shift; exact when B >= 0, 40-bit fill flagged for
 * negative sums). AR4 = B-low (stlm). MEM[1346] += 1 (addm).
 * B = MEM[AR4] unsigned (ldu; dark computed address). AR4 = 1351;
 * A = MEM[1346] + MEM[1351] (add dual); A >>= 16 logical (sftl
 * a,-16; same negative-flag); AR4 = A-low (stlm). Settle nops
 * (comments). A = MEM[AR4] unsigned (ldu; dark computed address).
 * Call 0734. Port 15 = cell 0x8 (portw *(0x8),15; cell 0x8 is the
 * AL-alias slot per the 2875 precedent, in-span writer unbound --
 * volatile cell read, emulator ground truth, flagged). rpt #2 nop
 * (3 settle cycles, comment per 2875). A = MEM[AR3=1346], AR3 =
 * 1347 (ld *ar3+). MEM[0x263A] |= 2 (orm). A -= MEM[1347] (sub
 * *ar3,a). A >= 0 joins L28CB (bc 0x28cb,ageq; in-span label).
 * Else MEM[0x263A] &= ~3 (andm #-3). A == 0 stores 0 to MEM[1347]
 * (xc 2,aeq over the 2-word st, exact). B = MEM[AR4-computed] via
 * the dark sink (bacc b; B is the ldu-loaded residue,
 * terminal-branch dark-sink per 5b26). A/B/ARs dead after (void).
 */
extern void sub_0732(void);                          /* dark, no symbol */
extern void sub_0734(void);                          /* dark, no symbol */
extern void port_write_15(int v);                    /* port 15 (2875 precedent) */
extern void dark_28A5_target(int addr);              /* bacc b (dark computed) */

void frag_28A5(void)
{
    long a;
    long b;
    int *ar3;
    int *ar4;
    sub_0732();                                      /* call 0x732 */
    ar3 = (int *)(long)1346;                         /* stm #1346,ar3 */
    ar4 = (int *)(long)1350;                         /* stm #1350,ar4 */
    b = (long)*ar3 + (long)*ar4;                     /* add *ar3,*ar4,b */
    b = (long)((unsigned long)b >> 16);              /* sftl b,-16 (logical) */
    ar4 = (int *)(long)(b & 0xFFFF);                 /* stlm b,ar4 */
    *ar3 += 1;                                       /* addm #1,*ar3 */
    b = (long)(unsigned)*ar4;                        /* ldu *ar4,b */
    ar4 = (int *)(long)1351;                         /* stm #1351,ar4 */
    a = (long)*ar3 + (long)*ar4;                     /* add *ar3,*ar4,a */
    a = (long)((unsigned long)a >> 16);              /* sftl a,-16 (logical) */
    ar4 = (int *)(long)(a & 0xFFFF);                 /* stlm a,ar4 */
    /* nop; nop (settles, no state) */
    a = (long)(unsigned)*ar4;                        /* ldu *ar4,a */
    sub_0734();                                      /* call 0x734 */
    /* nop (settle) */
    port_write_15(*(volatile int *)0x8);              /* portw *(0x8),15 */
    /* rpt #2 nop (3 settle cycles) */
    a = (long)*ar3++;                                /* ld *ar3+,a */
    *(volatile int *)0x263A |= 2;                    /* orm #2,*(0x263a) */
    a -= (long)*ar3;                                 /* sub *ar3,a */
    if (a >= 0)                                      /* bc 0x28cb,ageq */
        goto l28cb;
    *(volatile int *)0x263A &= -3;                   /* andm #-3,*(0x263a) */
l28cb:
    if (a == 0)                                      /* xc 2,aeq */
        *ar3 = 0;                                    /* st #0,*ar3 */
    dark_28A5_target((int)(b & 0xFFFF));             /* bacc b */
}
