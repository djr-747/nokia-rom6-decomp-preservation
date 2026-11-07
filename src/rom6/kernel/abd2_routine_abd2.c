/* ROM6 0xABD2 ROUTINE_ABD2 -- 53w select-and-scan loop.
 * Verified encoding: src/rom6/kernel/abd2_routine_abd2.asm (recombine MATCH).
 * ORIGIN 0xABD2
 * EXPECT: F074 0596 4A13 4A12 4A16 F274 71A3 7216 022D F074 71D8 8A16 8A12 8A13 7714 050B 1084 F844 AC22 1082 80F8 0060 7715 001F 7712 25A1 4912 01F8 265C F310 0001 8914 F495 F495 1184 F520 F84C AC00 61F8 263A 1000 F820 AC00 69F8 263A 0400 6F92 0D20 F84D AC07 6C8D AC00 FC00
 *
 * Intent: Runs sub_0596 (low-zone, flagged). AR3/
 * AR2/AR6-save (pshm, caller-live, balanced by the
 * popms, comments only); the calld delay (AR6 =
 * cell 0x22D) runs first, then frag_71A3 with entry
 * AR2/AR3; then scale_3EB8_leaf_71D8 with dark A
 * (int intake) and entry AR3, result ignored.
 * AR4 = 1291; A = *(AR4); nonzero tail-calls
 * frag_AC22 and returns (bc aneq). Else A =
 * *(AR2-entry); cell 0x60 = A-low; AR5 = 31
 * (register int); AR2 = 9633; B = AR2 register
 * value (ldm); B += cell 0x265C (SXM flagged);
 * B -= 1 (sub #1,b); AR4 = B-low (stlm). B =
 * *(AR4) - A (ld then sub a,b: dst -= src);
 * nonzero joins the C0 scan (bc bneq); else bit
 * 12 of cell 0x263A clear joins too (bitf; bc
 * ntc), else the bit sets (orm #1024) and falls
 * in. Scan C0 (AR5 = 31 passes): B = *(AR2++) -
 * A (sub 4-op shift 0: dst = Smem - src per dd77;
 * the 0D20 word is the shift-0 extension, not a
 * -32 shift -- binutils rejects out-of-range
 * shifts); zero tail-calls frag_AC07 and returns
 * (bc beq); else AR5-- != 0 repeats (banz
 * test-then-dec); AR5 exhausted falls to the ret.
 * Entry AR2/AR3 caller-live; A/B/AR4/AR5/AR6
 * in-span (A dark into 71d8, flagged).
 * EXPECT from the image.
 */
extern void sub_0596(void); /* low-zone unsourced, flagged */
extern void frag_71A3(int *ar2_in, int *ar3_in);
extern int scale_3EB8_leaf_71D8(int a_live, int *par3);
extern void frag_AC22(void);
extern void frag_AC07(void);

void routine_ABD2(int *ar2_in, int *ar3_in)
{
    long a;   /* live-in (dark, flagged) until ld */
    long b;
    int *ar2 = ar2_in;   /* entry AR2 (caller-live) */
    int *ar3 = ar3_in;   /* entry AR3 (caller-live) */
    int *ar4;
    int ar5v;
    int *ar6;

    sub_0596();                                            /* call 0x596 */
    /* pshm ar3/ar2/ar6 (balanced by popms; caller-live, comments only) */
    ar6 = (int *)(long)*(volatile int *)0x22D;             /* calld delay (runs first) */
    frag_71A3(ar2, ar3);                                   /* calld 0x71a3 */
    (void)scale_3EB8_leaf_71D8((int)a, ar3);              /* call 0x71d8 */
    /* popm ar6/ar2/ar3 (restore entry; AR6 value above unobserved after) */
    ar4 = (int *)(long)1291;                               /* stm #1291,ar4 */
    a = (long)*ar4;                                        /* ld *ar4,a */
    if (a != 0L) {                                         /* bc 0xac22,aneq */
        frag_AC22();                                       /* b 0xac22 (tail) */
        return;
    }
    a = (long)*ar2;                                        /* ld *ar2,a */
    *(volatile int *)0x60 = (int)(a & 0xFFFFL);            /* stl a,*(0x60) */
    ar5v = 31;                                             /* stm #31,ar5 */
    ar2 = (int *)(long)9633;                               /* stm #9633,ar2 */
    b = (long)ar2;                                         /* ldm ar2,b */
    b += (long)*(volatile int *)0x265C;                    /* add *(0x265c),b (SXM flagged) */
    b -= 1L;                                               /* sub #1,b */
    ar4 = (int *)(long)(b & 0xFFFFL);                      /* stlm b,ar4 */
    /* nop; nop */
    b = (long)*ar4;                                        /* ld *ar4,b */
    b -= a;                                                /* sub a,b (B = B - A) */
    if (b != 0L)                                           /* bc 0xac00,bneq */
        goto lane_c0;
    if ((*(volatile int *)0x263A & 4096) == 0)             /* bitf; bc ntc */
        goto lane_c0;
    *(volatile int *)0x263A |= 1024;                       /* orm #1024,*(0x263a) */
    /* falls into lane_c0 */
lane_c0:
    b = (long)*ar2++ - a;                                  /* sub *ar2+,a,b */
    if (b == 0L) {                                         /* bc 0xac07,beq */
        frag_AC07();                                       /* b 0xac07 (tail) */
        return;
    }
    if (ar5v-- != 0)                                       /* banz 0xac00 */
        goto lane_c0;
    /* ret (AR5 exhausted) */
}
