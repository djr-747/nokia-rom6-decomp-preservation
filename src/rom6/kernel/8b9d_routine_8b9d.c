/* ROM6 0x8B9D ROUTINE_8B9D -- 54w rounded-MAC viper lane.
 * Verified encoding: src/rom6/kernel/8b9d_routine_8b9d.asm (recombine MATCH).
 * ORIGIN 0x8B9D
 * EXPECT: 4494 7713 2F28 308B F272 8BCE 7712 1107 2382 F620 4592 F789 E65C 2382 F620 4592 F789 E65C 2382 F620 4592 F789 E65C 2382 F620 4592 F789 E65C 2382 F620 4592 F789 E65C 2382 F620 4592 F789 E65C 2382 F620 4592 F789 E6DC 2382 F620 4592 F789 E654 82DA C8A2 822C FE00 7712 3090
 *
 * Intent: Two entries (8B9D lane falls into the
 * 8B9E main; 389c pattern). Lane: A = *(AR4++) <<
 * 16. Main: AR3 = 12072; T = *(AR3--); the rptbd
 * delay (AR2 = 4359) runs first, then the block
 * 8BA5-8BCE runs BRC + 1 passes (BRC entry-dark,
 * flagged; callers @8B51/69/83/98 carry it). Each
 * pass: six identical quads B = round(*(AR2) x T)
 * >> 16 (mpyr, 22f3 form, FRCT flagged); A -= B
 * (sub b,a: dst -= src); B = *(AR2++) << 16 (SXM
 * flagged); B += round(T x A-high) (macar t,b:
 * p then (B + p + 0x8000) & ~0xFFFF, 8ddb oracle
 * form, FRCT doubling dark, flagged);
 * *(AR2) = B-low with AR2 += AR0-live in
 * parallel with T = *(AR3--) (st||ld, no hazard;
 * +0% steps per 351d linear convention, BK wrap
 * flagged). Then the +0% quad (AR3 += AR0-live),
 * the -1 quad (AR2--, AR3--), *(AR2) = A-high
 * with AR2 += AR0-live (sth +0%), and the
 * same-address pair tmp = *(AR4), *(AR4) = A-low,
 * A = tmp << 16, AR4++ (parallel st||ld reads
 * pre-store, SXM dark, 8ddb form). Tail: cell
 * 0x2C = A-high (sth); retd with its delay (AR2 =
 * 12432) running before the return. Entry BRC/
 * AR4/AR0/A caller-live dark. Out ARs/cells/A/B.
 * EXPECT from the image.
 */
void routine_8B9E(int brc_live, int *ar4_in, long a_live, int ar0_live);
void lane_8B9D(int brc_live, int *ar4_in, int ar0_live);

void lane_8B9D(int brc_live, int *ar4_in, int ar0_live)
{
    long a;

    a = (long)*ar4_in++ << 16;                                     /* ld *ar4+,16,a */
    routine_8B9E(brc_live, ar4_in, a, ar0_live);
}

void routine_8B9E(int brc_live, int *ar4_in, long a_live, int ar0_live)
{
    long a = a_live;
    long b;
    long p;
    int *ar2;
    int *ar3;
    int *ar4 = ar4_in;   /* entry AR4 (caller-live, flagged) */
    int t;
    int tmp;
    int i;
    int j;

    ar3 = (int *)(long)12072;                                      /* stm #12072,ar3 */
    t = *ar3--;                                                    /* ld *ar3-,t */
    /* rptbd 0x8bce (delay stm #4359,ar2 runs first) */
    ar2 = (int *)(long)4359;
    for (i = 0; i < brc_live + 1; i++) {                           /* rptbd block */
        for (j = 0; j < 6; j++) {
            b = ((long)*ar2 * (long)t + 0x4000L) >> 16;            /* mpyr *ar2,b */
            a -= b;                                                /* sub b,a */
            b = (long)*ar2++ << 16;                                /* ld *ar2+,16,b */
            p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);     /* macar t,b */
            b = (b + p + 0x8000L) & ~0xFFFFL;
            *ar2 = (int)(b & 0xFFFFL);                             /* st b,*ar2+0% */
            ar2 += ar0_live;                                       /* +0% (wrap flagged) */
            t = *ar3--;                                            /* ld *ar3-,t */
        }
        b = ((long)*ar2 * (long)t + 0x4000L) >> 16;                /* mpyr */
        a -= b;
        b = (long)*ar2++ << 16;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);         /* macar */
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar2 = (int)(b & 0xFFFFL);                                 /* st b,*ar2+0% */
        ar2 += ar0_live;
        t = *ar3;                                                  /* ld *ar3+0%,t */
        ar3 += ar0_live;                                           /* +0% (wrap flagged) */
        b = ((long)*ar2 * (long)t + 0x4000L) >> 16;                /* mpyr */
        a -= b;
        b = (long)*ar2++ << 16;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);         /* macar */
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar2 = (int)(b & 0xFFFFL);                                 /* st b,*ar2- */
        ar2--;
        t = *ar3--;                                                /* ld *ar3-,t */
        *ar2 = (int)((a >> 16) & 0xFFFFL);                         /* sth a,*ar2+0% */
        ar2 += ar0_live;                                           /* +0% (wrap flagged) */
        tmp = *ar4;                                                /* st a,*ar4 || ld *ar4+,a */
        *ar4 = (int)(a & 0xFFFFL);                                 /* (store uses issue-time A/AR4) */
        a = (long)tmp << 16;                                       /* (load reads pre-store) */
        ar4++;
    }
    *(volatile int *)0x2C = (int)((a >> 16) & 0xFFFFL);            /* sth a,0x2c */
    /* retd (delays run before the return) */
    ar2 = (int *)(long)12432;                                      /* delay: stm #12432,ar2 */
}
