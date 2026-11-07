/* ROM6 0x7FF4 SUB_7FF4 -- 57w copy plus select into 0x802D/0x802F.
 * Verified encoding: src/rom6/kernel/7ff4_sub_7ff4.asm (recombine MATCH).
 * ORIGIN 0x7FF4
 * EXPECT: F074 059E 10F8 2650 F844 805A 10F8 25D6 F844 8009 E906 F074 4590 7714 25D8 EC03 7094 B1CD F171 0006 8194 7714 25D6 7694 0000 11F8 2645 F768 60F8 250F 0022 F820 8029 60F8 34BF 0003 F820 801F 61F8 3490 0001 F830 802D 60F8 34BF 0001 F830 802D 60F8 34BF 0004 F830 802D 1BF8 2644 F073 802F
 *
 * Intent: Runs dark SUB_059E (call, forward extern void). Cell 0x2650
 * nonzero tail-enters dark 0x805A (bc aneq; A rides, void + note); cell
 * 0x25D6 nonzero tail-enters dark 0x8009 (same). Runs ROUTINE_4590 with
 * B = 6 (call, C: routine_4590(b_in)). AR4 = 9688; 4 copies of cell
 * 0xB1CD via *AR4++ (rpt #3 + mvkd absolute-source load-store, 4 runs).
 * RPTZ B,#6 zeroes B and repeats 7 times (ti-c54x op_rptz.c: accumulator
 * zero plus RC = lk): 7 stores of B-low = 0 via *AR4++ (AR4 to 9699).
 * AR4 = 9686; *AR4++ = 0 (st). B = cell 0x2645 sign-extended (ld);
 * B <<= 8 (sfta). Cell(DP 8) != 34 tail-enters dark 0x8029 (bc ntc, void
 * + note); cell 0x34BF != 3 tail-enters dark 0x801F (void + note). Bit 0
 * of cell 0x3490 set tail-enters 0x802D with B-live (bc tc; has .asm with
 * bd, forward extern void frag_802D(long b_live)). Cell 0x34BF == 1 or ==
 * 4 (cmpm pair) tail-enters 0x802D the same way. Else B |= cell 0x2644
 * zero-extended (or Smem: zero extension per ti-c54x op_or_smem.c) and
 * tail-enters dark 0x802F with B-live (b; forward extern void
 * frag_802F(long b_live), same pattern as B61F). A/B internal; AR4 cursor
 * local. Bound 7FF4-802C (exit F073@802B->802F + operand 802C).
 */
extern void sub_059E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_805A(void); /* joins 802d_frag_802d interior @+0x2D; see docs/evidence/extern-triage.md */
extern void frag_8009(void); /* joins 7ff4_sub_7ff4 interior @+0x15; see docs/evidence/extern-triage.md */
extern void routine_4590(int b_in);
extern void frag_8029(void); /* joins 7ff4_sub_7ff4 interior @+0x35; see docs/evidence/extern-triage.md */
extern void frag_801F(void); /* joins 7ff4_sub_7ff4 interior @+0x2B; see docs/evidence/extern-triage.md */
extern void frag_802D(long b_live); /* joins 802d_frag_802d; see docs/evidence/extern-triage.md */
extern void frag_802F(long b_live); /* joins 802d_frag_802d interior @+0x2; see docs/evidence/extern-triage.md */

void frag_7FF4(void)
{
    long a;
    long b;
    int *par4;
    int i;

    sub_059E();                                        /* call 0x59e */
    a = (long)*(volatile int *)0x2650;                 /* ld *(0x2650),a */
    if (a != 0) {                                      /* bc 0x805a,aneq */
        frag_805A();                                   /* (A rides, noted) */
        return;
    }
    a = (long)*(volatile int *)0x25D6;                 /* ld *(0x25d6),a */
    if (a != 0) {                                      /* bc 0x8009,aneq */
        frag_8009();                                   /* (A rides, noted) */
        return;
    }
    routine_4590(6);                                   /* ld #6,b; call */
    par4 = (int *)9688;                                /* stm #9688,ar4 */
    for (i = 0; i < 4; i++)                            /* rpt #3 + mvkd */
        *par4++ = *(volatile int *)0xB1CD;
    b = 0L;                                            /* rptz b,#6: zero */
    for (i = 0; i < 7; i++)                            /* repeat 7x */
        *par4++ = (int)(b & 0xFFFF);                   /* stl b,*ar4+ */
    par4 = (int *)9686;                                /* stm #9686,ar4 */
    *par4++ = 0;                                       /* st #0,*ar4+ */
    b = (long)*(volatile int *)0x2645;                 /* ld *(0x2645),b */
    b <<= 8;                                           /* sfta b,8 */
    if (*(volatile int *)0x8 != 34) {                  /* cmpm; bc ntc */
        frag_8029();
        return;
    }
    if (*(volatile int *)0x34BF != 3) {                 /* cmpm; bc ntc */
        frag_801F();
        return;
    }
    if (*(volatile int *)0x3490 & 1) {                 /* bitf; bc tc */
        frag_802D(b);
        return;
    }
    if (*(volatile int *)0x34BF == 1) {                 /* cmpm; bc tc */
        frag_802D(b);
        return;
    }
    if (*(volatile int *)0x34BF == 4) {                 /* cmpm; bc tc */
        frag_802D(b);
        return;
    }
    b |= (unsigned short)*(volatile int *)0x2644;      /* or (zero-ext) */
    frag_802F(b);                                      /* b 0x802f tail */
}
