/* ROM6 0x9146 BUTTERFLY_9146 -- 69w (span 9146-918A, single entry).
 * Verified encoding: src/rom6/modem/9146_butterfly_9146.asm (recombine MATCH).
 * ORIGIN 0x9146
 * EXPECT: 7712 3138 4497 3D97 3F87 8392 F784 8392 F501 8392 F784 8392 4387 4397 8392 F784 8392 F521 8392 F784 8382 4A15 4A14 7715 3138 7714 3448 4495 1A95 4595 1B95 E5B6 E5BA 7715 3120 8295 8195 8395 8095 E56B E54B E58B E5AB E56B E54B E50B E52B 8295 8195 8395 8095 8395 8095 8295 8195 E58B E5AB E56B E54B E58B E5AB E52B E50B 8395 8095 8295 8185 8A14 8A15
 *
 * Intent: Viterbi-butterfly plus deinterleave shuffle (9118
 * sibling; falls into the 918B ret -- the 918B span owns that
 * word per the abut convention, modeled as a plain return).
 * Entry AR7 (butterfly cursor), AR4/AR5 (pshm-saved, stm-
 * reseated, popm-restored: net preserved, carried as params
 * and restored through locals) live; entry A/B unread (both
 * recomputed); void. AR2 = 12600 local. Butterfly: A =
 * *AR7++ << 16 (ld); B = A + (*AR7++ << 16) (add syntax-3,
 * catalog line 59); B += *AR7 << 16 (add, no step); sth
 * B-high to *AR2++ (plain STH bits 31-16 per op_sth_smem,
 * no ASM input); B = -B (neg, LONG_MIN edge flagged per the
 * e54b convention); sth; B += A << 1 (add a,1,b: dst =
 * dst_old + (src << SHIFT) per the op_arithmetic leaf -- the
 * 2d8f b = a + ... precedent is inconsistent with the leaf
 * and flagged as a suspect, see worklog); sth; B = -B; sth;
 * B -= *AR7 << 16; B -= *AR7++ << 16 (sub syntax-3, catalog
 * line 85); sth; B = -B; sth; B -= A << 1 (sub a,1,b, same
 * leaf rule); sth; B = -B; sth (no step). pshm ar5/ar4
 * (entry values saved to locals). AR5 = 12600, AR4 = 13384
 * (stm). Combine: A = *AR5++ << 16; A |= *AR5++ signed (or
 * Smem, sign-extended, 40-bit flagged); B = *AR5++ << 16;
 * B |= *AR5++ signed. Shuffle (all single-word moves, 3273
 * shape): mvdd *ar5+ to *ar4-, *ar5+ to *ar4+; AR5 = 12576;
 * sth/stl ladder alternating A/B halves to *AR5++;
 * six-mvdd block (*ar4-/*ar2-/*ar2+/*ar4+/*ar4-/*ar2- to
 * *ar5+); second sth/stl ladder; eight-mvdd block (*ar2+/
 * *ar4+/*ar4-/*ar2-/*ar2+/*ar4+/*ar4/*ar2 to *ar5+); final
 * sth/stl ladder; popm restores AR4/AR5 (LIFO); falls into
 * the 918B ret. 40-bit wrap/OVM flagged throughout (long
 * holds 32 bits); SXM dark (no in-span ST1 setup, sign-
 * extended forms assume SXM = 1 per the modem convention,
 * flagged).
 */
void frag_9146(int *ar4_in, int *ar5_in, int *ar7_in)
{
    long a;
    long b;
    int *ar2 = (int *)12600;                         /* stm #12600,ar2 */
    int *ar4 = ar4_in;
    int *ar5 = ar5_in;
    int *ar7 = ar7_in;
    int *ar4e;                                       /* pshm ar4 image */
    int *ar5e;                                       /* pshm ar5 image */
    a = (long)*ar7++ << 16;                          /* ld *ar7+,16,a */
    b = a + ((long)*ar7++ << 16);                    /* add *ar7+,16,a,b */
    b += (long)*ar7 << 16;                           /* add *ar7,16,b */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b = -b;                                          /* neg b (edge flagged) */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b += a << 1;                                     /* add a,1,b (dst_old + src<<1) */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b = -b;                                          /* neg b */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b -= (long)*ar7 << 16;                           /* sub *ar7,16,b */
    b -= (long)*ar7++ << 16;                         /* sub *ar7+,16,b */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b = -b;                                          /* neg b */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b -= a << 1;                                     /* sub a,1,b (dst_old - src<<1) */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar2+ */
    b = -b;                                          /* neg b */
    *ar2 = (int)((b >> 16) & 0xFFFFL);               /* sth b,*ar2 */
    ar5e = ar5;                                      /* pshm ar5 */
    ar4e = ar4;                                      /* pshm ar4 */
    ar5 = (int *)12600;                              /* stm #12600,ar5 */
    ar4 = (int *)13384;                              /* stm #13384,ar4 */
    a = (long)*ar5++ << 16;                          /* ld *ar5+,16,a */
    a |= (long)*ar5++;                               /* or *ar5+,a (sign-extended) */
    b = (long)*ar5++ << 16;                          /* ld *ar5+,16,b */
    b |= (long)*ar5++;                               /* or *ar5+,b */
    *ar4-- = *ar5++;                                 /* mvdd *ar5+,*ar4- */
    *ar4++ = *ar5++;                                 /* mvdd *ar5+,*ar4+ */
    ar5 = (int *)12576;                              /* stm #12576,ar5 */
    *ar5++ = (int)((a >> 16) & 0xFFFFL);             /* sth a,*ar5+ */
    *ar5++ = (int)(b & 0xFFFFL);                     /* stl b,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar5+ */
    *ar5++ = (int)(a & 0xFFFFL);                     /* stl a,*ar5+ */
    *ar5++ = *ar4--;                                 /* mvdd *ar4-,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = *ar4++;                                 /* mvdd *ar4+,*ar5+ */
    *ar5++ = *ar4--;                                 /* mvdd *ar4-,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = *ar4;                                   /* mvdd *ar4,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFFL);             /* sth a,*ar5+ */
    *ar5++ = (int)(b & 0xFFFFL);                     /* stl b,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar5+ */
    *ar5++ = (int)(a & 0xFFFFL);                     /* stl a,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar5+ */
    *ar5++ = (int)(a & 0xFFFFL);                     /* stl a,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFFL);             /* sth a,*ar5+ */
    *ar5++ = (int)(b & 0xFFFFL);                     /* stl b,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = *ar4++;                                 /* mvdd *ar4+,*ar5+ */
    *ar5++ = *ar4--;                                 /* mvdd *ar4-,*ar5+ */
    *ar5++ = *ar2--;                                 /* mvdd *ar2-,*ar5+ */
    *ar5++ = *ar2++;                                 /* mvdd *ar2+,*ar5+ */
    *ar5++ = *ar4++;                                 /* mvdd *ar4+,*ar5+ */
    *ar5++ = *ar4;                                   /* mvdd *ar4,*ar5+ */
    *ar5++ = *ar2;                                   /* mvdd *ar2,*ar5+ */
    *ar5++ = (int)((b >> 16) & 0xFFFFL);             /* sth b,*ar5+ */
    *ar5++ = (int)(a & 0xFFFFL);                     /* stl a,*ar5+ */
    *ar5++ = (int)((a >> 16) & 0xFFFFL);             /* sth a,*ar5+ */
    *ar5 = (int)(b & 0xFFFFL);                       /* stl b,*ar5 */
    ar4 = ar4e;                                      /* popm ar4 (LIFO restore) */
    ar5 = ar5e;                                      /* popm ar5 */
    /* fall into 918B ret */
}
