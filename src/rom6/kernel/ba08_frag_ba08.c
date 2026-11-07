/* ROM6 0xBA08 FRAG_BA08 -- 34w threshold/gate lane.
 * Verified encoding: src/rom6/kernel/ba08_frag_ba08.asm (recombine MATCH).
 * ORIGIN 0xBA08
 * EXPECT: 7681 0006 6181 0002 F820 BA22 10F8 2ADB F010 0005 F847 BA22 E80A 00F8 2ADF 08F8 2AE0 F842 BA22 62F8 2AE9 599A 40F8 2AE8 F846 BA07 7681 0005 10F8 2AFD FE44 81F8 2ADB FE00
 *
 * Intent: Multi-gate threshold lane with two return
 * shapes. Cell *AR1 = 6; TC = bit1 of *AR1 (BITF any-bit);
 * TC clear joins the BA22 store leg; else A = cell
 * 0x2ADB, A -= 5, A <= 0 joins BA22; else A = 10,
 * A += cell 0x2ADF << 16, A -= cell 0x2AE0 << 16,
 * A >= 0 joins BA22; else A = cell 0x2AE9 * 22938
 * (MPY Smem,#lk), A -= cell 0x2AE8 << 16, A > 0 transfers
 * to BA07 -- the predecessor B948 span's RETD word, whose
 * 2 delay words are this span's head st #6 (cell *AR1 =
 * 6) -- then returns (shared-word delay spill, same shape
 * as the BA2A spill noted in the asm header). BA22 leg:
 * cell *AR1 = 5; A = cell 0x2AFD; RCD ANEQ (delayed
 * conditional return): the stl + retd words run either
 * way -- cell 0x2ADB = BL, then return via the scheduled
 * RCD or the falling-through RETD (whose delays spill
 * onto BA2A-BA2B per the header). No live entry state
 * except *AR1 (dark, flagged) and B for the tail store
 * (dark, flagged).
 * (Wave-13: EXPECT from the image; RETC-delayed shape
 * per the 2-delay-word rule.)
 */
void frag_BA08(void)
{
    long a;
    long b;  /* tail store source (dark, flagged) */
    int *ar1;  /* live-in (dark, flagged) */
    int tc;

    *ar1 = 6;                                                      /* st #6,*ar1 */
    tc = ((*ar1 & 2) != 0);                                        /* bitf *ar1,#2 */
    if (!tc)                                                       /* bc 0xba22,ntc */
        goto lba22;
    a = (long)*(volatile int *)0x2ADB;                             /* ld *(0x2adb),a */
    a -= 5;                                                        /* sub #5,a */
    if (a <= 0)                                                    /* bc 0xba22,aleq */
        goto lba22;
    a = 10;                                                        /* ld #10,a */
    a += (long)*(volatile int *)0x2ADF << 16;                      /* add *(0x2adf),a */
    a -= (long)*(volatile int *)0x2AE0 << 16;                      /* sub *(0x2ae0),a */
    if (a >= 0)                                                    /* bc 0xba22,ageq */
        goto lba22;
    a = (long)*(volatile int *)0x2AE9 * 22938L;                    /* mpy *(0x2ae9),#22938,a */
    a -= (long)*(volatile int *)0x2AE8 << 16;                      /* sub *(0x2ae8),16,a */
    if (a > 0) {                                                   /* bc 0xba07,agt */
        *ar1 = 6; /* (lands on predecessor RETD; this head st runs as its delay words) */
        return;
    }
lba22:
    *ar1 = 5;                                                      /* st #5,*ar1 (BA22 join) */
    a = (long)*(volatile int *)0x2AFD;                             /* ld *(0x2afd),a */
    /* rcd aneq (delayed conditional return; delays run either way): */
    *(volatile int *)0x2ADB = (int)(b & 0xFFFFL);                 /* stl b,*(0x2adb) */
    /* retd (fall-through path; delays spill to BA2A-BA2B) */
    /* ret */
    (void)a;
}
