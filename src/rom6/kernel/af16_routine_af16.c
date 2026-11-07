/* ROM6 0xAF16 ROUTINE_AF16 -- 40w scatter loop.
 * Verified encoding: src/rom6/kernel/af16_routine_af16.asm (recombine MATCH).
 * ORIGIN 0xAF16
 * EXPECT: 11F8 3490 F330 0007 81F8 0015 00F8 0015 80F8 0015 1193 F310 0002 81F8 001A 7185 0012 F072 AF3C 7193 0014 1086 F010 0001 F843 AF3D F845 AF39 80F8 0011 47F8 0011 E5A8 F073 AF3A E5A8 6D96 F495 F495 FC00
 *
 * Intent: B = *(0x3490) (ld, SXM dark, flagged); B &= 7;
 * *(0x15) = B-low; A += *(0x15)<<16 (A live-in dark); *(0x15)
 * = A-low; B = *(AR3++) (AR3 dark); B -= 2; *(0x1A) = B-low;
 * AR2 = *(AR5) (mvdk to MMR 0x12 = AR2 per C54x map, AR5
 * dark, flagged). RPTB block (BRC dark, flagged; exits via
 * bc-alt or BRC exhaustion): AR4 = *(AR3++) (mvdk to MMR
 * 0x14 = AR4); A = *(AR6) (AR6 dark); A -= 1; A < 0 returns
 * (bc alt); A == 0 copies one word *(AR2++) = *(AR4++)
 * (aeq lane); else *(0x11) = A-low and copies A+1 words
 * (rpt *(0x11) runs count+1 per RPTZ-precedent, b skips lane
 * 2); AR6++ (mar); repeat. A/B/ARs dark as noted; out
 * cells/ARs.
 * EXPECT from the image.
 */
void routine_AF16(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar5;  /* live-in (dark, flagged) */
    int *ar6;  /* live-in (dark, flagged) */
    int brc;  /* live-in (dark, flagged) */
    int n;
    int i;
    int j;

    b = (long)*(volatile int *)0x3490;                        /* ld *(0x3490),b (SXM dark) */
    b &= 7L;                                                 /* and #7,b */
    *(volatile int *)0x15 = (int)(b & 0xFFFFL);               /* stl b,*(0x15) */
    a += (long)*(volatile int *)0x15 << 16;                  /* add *(0x15),a */
    *(volatile int *)0x15 = (int)(a & 0xFFFFL);               /* stl a,*(0x15) */
    b = (long)*ar3++;                                        /* ld *ar3+,b */
    b -= 2;                                                  /* sub #2,b */
    *(volatile int *)0x1A = (int)(b & 0xFFFFL);              /* stl b,*(0x1a) */
    ar2 = (int *)(long)*ar5;                                 /* mvdk *ar5,0x12 (AR2 = *(AR5)) */
    /* rptb 0xaf3c */
    for (i = 0; i <= (unsigned)brc; i++) {                   /* (BRC+1 incl. wrap; BRC dark, flagged) */
        ar4 = (int *)(long)*ar3++;                           /* mvdk *ar3+,0x14 (AR4 = *(AR3++)) */
        a = (long)*ar6;                                      /* ld *ar6,a (SXM dark) */
        a -= 1;                                              /* sub #1,a */
        if (a < 0)                                           /* bc 0xaf3d,alt */
            return;
        if (a == 0) {                                        /* bc 0xaf39,aeq */
            *ar2++ = *ar4++;                                 /* mvdd *ar4+,*ar2+ */
        } else {
            *(volatile int *)0x11 = (int)(a & 0xFFFFL);      /* stl a,*(0x11) */
            n = *(volatile int *)0x11;                       /* rpt *(0x11): runs n+1 */
            for (j = 0; j < n + 1; j++)
                *ar2++ = *ar4++;                             /* mvdd *ar4+,*ar2+ */
            /* b 0xaf3a (skips lane 2) */
        }
        ar6++;                                               /* mar *ar6+ */
        /* nop; nop */
    }
    /* ret (BRC exhaustion edge flagged dark) */
}
