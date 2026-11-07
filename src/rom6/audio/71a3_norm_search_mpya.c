/* ROM6 0x71A3 NORM_SEARCH_MPYA -- 53w.
 * Verified encoding: src/rom6/audio/71a3_norm_search_mpya.asm (recombine MATCH).
 * ORIGIN 0x71A3
 * EXPECT: F074 0598 1182 61F8 051F 0080 FA20 71BE 7715 3EA1 F210 03CF F843 71B8 F210 0400 0895 F273 71CB 770E 0010 F210 007C F847 71BE 7715 3ED6 6F95 0E20 FA47 71CB 770E 0010 6F95 0E20 6D95 F843 71D7 F073 71CD F484 6D95 F48F 3185 F648 3D83 F301 4000 76F8 000B 0000 8383 FC00
 *
 * Intent: Audio norm search with table select (callers in 7522).
 * Runs dark SUB_0598 (opaque; A/B outs dark residues, unbound
 * locals). B = *AR2-entry (ld; AR2 read-only param). TC =
 * (*(0x51F) & 128) != 0 (bitf, 5d38 polarity). bcd 0x71be,ntc: the
 * 2-word window (stm #16033,ar5 + sub #975,b,a) always runs (520C
 * word-count rule: AR5 = 16033, A = B - 975); NTC-taken jumps,
 * fall continues. bc 0x71b8,alt: ALT = A < 0 sign test (per the
 * op_branch_cond_common ground truth, COND_ALT 0x43 -- not A < B);
 * taken iff B < 975. 71B1 lane (B >= 975): A = B - 1024
 * (sub #1024,b,a); A -= *AR5++ (sub *ar5+,a; SXM assumed, flagged);
 * bd 0x71cb: unconditional delayed branch, delays stm #16,t (T =
 * 16) + A = B - 124 run always, then jump. 71B8 lane: A = B - 124;
 * aleq exits to 71BE (bc, A <= 0). Else AR5 = 16086 (stm); A = B -
 * *AR5++ (sub dual, 2-word form); bcd 0x71cb,aleq: delay stm #16,t
 * always runs (T = 16), aleq-taken jumps. Fall: A = B - *AR5++;
 * AR5++ (mar); alt (A < 0) exits via 71D7 (bc lands on the ret
 * word, skipping the store-back); else b 0x71cd skips neg+mar.
 * 71CB lane: A = -A (neg; LONG_MIN flagged); AR5++ (mar). 71CD
 * join: A <<= 16 (norm a; T = 16 on every arrival path, delay-stm
 * proven; 40-bit wrap flagged); B += 16 * *AR5 (mpya *ar5: MPYA
 * accumulates into B per the op_mpya_smem leaf, FRCT/OVM flagged);
 * A = B << 8 (ld b,8,a); B = A + (*(AR3-entry) << 16) (add dual,
 * AR3 read-only param, dark entry); B += 32768 (add #16384,1,b);
 * MEM[cell 0xB] = 0 (st #0 absolute; the reada-mailbox cell);
 * MEM[*AR3-entry] = B-high (sth b,*ar3); return. A/B outs dark
 * residues (void, flagged); T-out = 16 (not carried, flagged).
 */
extern void sub_0598(void);                          /* dark */

void frag_71A3(int *ar2_in, int *ar3_in)
{
    long a;
    long b;                                          /* unbound: SUB_0598 B residue */
    int *ar5;
    int t;
    sub_0598();                                      /* call 0x598 */
    b = (long)*ar2_in;                               /* ld *ar2,b */
    /* bitf *(0x51f),#128; bcd 0x71be,ntc */
    ar5 = (int *)(long)16033;                        /* bcd delay 1 (always) */
    a = b - 975;                                     /* bcd delay 2 (always) */
    if ((*(volatile int *)0x51F & 128) == 0)         /* bcd taken */
        goto l71be;
    if (a < 0)                                       /* bc 0x71b8,alt (A<0) */
        goto l71b8;
    a = b - 1024;                                    /* sub #1024,b,a */
    a -= (long)*ar5++;                               /* sub *ar5+,a */
    t = 16;                                          /* bd delay 1 */
    a = b - 124;                                     /* bd delay 2 */
    goto l71cb;                                      /* bd 0x71cb */
l71b8:
    a = b - 124;                                     /* sub #124,b,a */
    if (a <= 0)                                      /* bc 0x71be,aleq */
        goto l71be;
    ar5 = (int *)(long)16086;                        /* stm #16086,ar5 */
l71be:
    /* 71BE join (AR5 = 16033 via the bcd delay, or 16086 via stm) */
    a = b - (long)*ar5++;                            /* sub *ar5+,b,a */
    t = 16;                                          /* bcd delay (always) */
    if (a <= 0)                                      /* bcd 0x71cb,aleq taken */
        goto l71cb;
    a = b - (long)*ar5++;                            /* sub *ar5+,b,a */
    ar5++;                                           /* mar *ar5+ */
    if (a < 0)                                       /* bc 0x71d7,alt */
        return;                                      /* 71D7 = ret word */
    goto l71cd;                                      /* b 0x71cd */
l71cb:
    a = -a;                                          /* neg a */
    ar5++;                                           /* mar *ar5+ */
l71cd:
    if (t >= 0) {                                    /* norm a (op_norm_acc) */
        a <<= t;
    } else {
        a = (long)((unsigned long)a >> (unsigned)(-t));
    }
    b += (long)t * (long)*ar5;                       /* mpya *ar5 (B += T*MEM) */
    a = b << 8;                                      /* ld b,8,a */
    b = a + ((long)*ar3_in << 16);                   /* add *ar3,16,a,b */
    b += 32768L;                                     /* add #16384,1,b */
    *(volatile int *)0xB = 0;                        /* st #0,cell 0xB */
    *ar3_in = (int)((b >> 16) & 0xFFFF);             /* sth b,*ar3 */
}
