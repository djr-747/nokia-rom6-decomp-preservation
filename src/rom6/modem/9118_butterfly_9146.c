/* ROM6 0x9118 BUTTERFLY_9146 -- 46w head (span 9118-9145, ret @9145).
 * Verified encoding: src/rom6/modem/9118_butterfly_9146.asm (recombine MATCH).
 * ORIGIN 0x9118
 * EXPECT: 7712 3448 4497 4187 838A F784 8382 3C97 F584 4A15 7715 3120 8295 E58B E50B 8395 8395 E54B E58B 8295 8395 E54B E50B 8295 8295 E58B E50B 8395 E54B 8395 8295 E50B E58B 8295 8395 E54B E58B 8295 8395 E50B E54B 8395 8295 E50B 8A15 FC00
 *
 * Intent: FFT butterfly sum/difference + shuffle store (modem
 * engine; callers in 90BC/90D5 per the header). A = (*AR7++ << 16)
 * (ld *ar7+,16,a, 425f precedent); B = A - (*AR7 << 16) (sub
 * *ar7,16,a,b, 50B2 shifted-sub precedent). MEM[AR2] = B-high,
 * AR2-- (sth b,*ar2-); B = -B (neg b; LONG_MIN edge: HW wraps per
 * op_abs_acc with OVM as-is, C negation UB -- flagged);
 * MEM[AR2] = B-high (sth). A += (*AR7++ << 16) (add *ar7+,16,a);
 * B = -A (neg a,b; same edge flagged). AR5 entry preserved across
 * the lane (pshm/popm balanced, never read in-span -- comments only
 * per the 5d38 precedent); AR5 = 12576 local. Interleave: sth A/B
 * highs and mvdd *AR2<>/*AR5+ block moves per the op sequence
 * (sth = (high >> 16) & 0xFFFF per 5b26; mvdd per 5301), AR2 local
 * from 13384 (stm-created, walks, not carried), AR5 local walks.
 * popm restores AR5; return. AR7 entry-live advancing +2 (**,
 * 2e64 precedent). A/B dead after the stores (void).
 */
void frag_9118(int **ppar7)
{
    long a;
    long b;
    int *ar2 = (int *)(long)13384;                   /* stm #13384,ar2 (local) */
    int *ar5;
    int *ar7 = *ppar7;
    a = (long)*ar7++ << 16;                          /* ld *ar7+,16,a */
    b = a - ((long)*ar7 << 16);                      /* sub *ar7,16,a,b */
    *ar2-- = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar2- */
    b = -b;                                          /* neg b */
    *ar2 = (int)((b >> 16) & 0xFFFF);                /* sth b,*ar2 */
    a += (long)*ar7++ << 16;                         /* add *ar7+,16,a */
    b = -a;                                          /* neg a,b */
    /* pshm ar5 (balanced by popm; caller-live, comments only) */
    ar5 = (int *)(long)12576;                        /* stm #12576,ar5 (local) */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    /* popm ar5 */
    *ppar7 = ar7;                                    /* AR7-out = +2 */
}
