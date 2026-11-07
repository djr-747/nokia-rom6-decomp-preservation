/* ROM6 0x9C61 WRAP_9C61 -- 46w xor-fold loop.
 * Verified encoding: src/rom6/kernel/9c61_wrap_9c61.asm (recombine MATCH).
 * ORIGIN 0x9C61
 * EXPECT: 4916 F77F F310 0001 891A E800 F040 FFFF F84B 9C82 F272 9C81 6F82 0D58 F1C0 F330 00FF F300 DE54 8914 F0F8 1192 1C84 F1C0 F330 00FF F300 DE54 8914 F0F8 6F82 0D58 1C84 61F8 0016 0001 F820 9C8B 6F82 0D58 F074 9C8F F493 FE00 F030 FFFF
 *
 * Intent: B = AR6-value (ldm, AR6 dark, flagged); B >>= 1
 * arithmetic (sfta); B -= 1; BRC = B-low. A = 0; A |= -1
 * (A = -1). B < 0 skips the loop to the bitf tail (bc blt;
 * AR6 0/1 path). RPTBD block (exact BRC+1 incl. wrap; BRC
 * dark-derived, flagged; delays ld *ar2,-8,b = *(AR2)>>8
 * arithmetic, SXM dark, flagged, runs once): B ^= A
 * (acc-xor width masked by the following and#255, 40-bit
 * narrowing flagged); B &= 255; B += -8620; AR4 = B-low;
 * A = low32(A)>>8 logical (sftl, oracle); B = *(AR2++)
 * (SXM dark); A ^= *(AR4) zero-extended (upper preserved,
 * OR-like); B ^= A; B &= 255; B += -8620; AR4 = B-low;
 * A >>= 8; B = *(AR2)>>8; A ^= *(AR4). Tail: bit 0 of
 * *(0x16) set runs ld *ar2,-8,b + ROUTINE_9C8F (fall
 * through; the call redefines A/B, opaque here -- see its
 * C); clear skips to cmpl (bc ntc). A = ~A (cmpl);
 * retd delays and #-1,a (no-op mask, runs) then return.
 * AR2/AR6/entry A/B dark; T/C dead; out cells/ARs/A.
 * EXPECT from the image.
 */
void wrap_9C61(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar6;  /* live-in (dark, flagged) */
    int brc;  /* (dark: AR6-derived, flagged) */
    int i;

    b = (long)ar6;                                           /* ldm ar6,b */
    b = b >> 1;                                              /* sfta b,-1 (SXM-gated, flagged) */
    b -= 1;                                                  /* sub #1,b */
    brc = (int)(b & 0xFFFFL);                                /* stlm b,brc */
    a = 0;                                                   /* ld #0,a */
    a |= -1L;                                                /* or #-1,a */
    if (b >= 0) {                                            /* bc 0x9c82,blt (skipped when < 0) */
        /* rptbd 0x9c81: delay runs once */
        b = (long)*ar2 >> 8;                                 /* ld *ar2,-8,b (SXM dark) */
        for (i = 0; i <= (unsigned)brc; i++) {               /* (BRC+1 incl. wrap; dark) */
            b ^= a;                                          /* xor a,b (width masked below) */
            b &= 255L;                                       /* and #255,b */
            b += -8620;                                      /* add #-8620,b */
            ar4 = (int *)(b & 0xFFFFL);                       /* stlm b,ar4 */
            a = (long)((unsigned long)a >> 8);               /* sftl a,-8 (oracle) */
            b = (long)*ar2++;                                /* ld *ar2+,b (SXM dark) */
            a ^= (unsigned int)*ar4;                         /* xor *ar4,a (upper kept) */
            b ^= a;                                          /* xor a,b */
            b &= 255L;                                       /* and #255,b */
            b += -8620;                                      /* add #-8620,b */
            ar4 = (int *)(b & 0xFFFFL);                       /* stlm b,ar4 */
            a = (long)((unsigned long)a >> 8);               /* sftl a,-8 */
            b = (long)*ar2 >> 8;                             /* ld *ar2,-8,b */
            a ^= (unsigned int)*ar4;                         /* xor *ar4,a */
        }
    }
    if ((*(volatile int *)0x16 & 1) != 0) {                  /* bitf, bc 0x9c8b,ntc */
        b = (long)*ar2 >> 8;                                 /* ld *ar2,-8,b */
        routine_9C8F();                                      /* call 0x9c8f (redefines A/B, opaque) */
    }
    a = ~a;                                                  /* cmpl a */
    a &= -1L;                                                /* and #-1,a (retd delay, no-op) */
    /* retd */
}
