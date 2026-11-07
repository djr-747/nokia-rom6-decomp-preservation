/* ROM6 0x8956 MAX_LOOP_8956 -- 93w (live 8956-898F).
 * Verified encoding: src/rom6/kernel/8956_max_loop_8956.asm (recombine MATCH).
 * ORIGIN 0x8956
 * EXPECT: 6184 0001 FA20 8976 6984 0001 6884 FFF9 6984 0004 7712 055A 1082 F110 0005 F84A 89B3 F000 0001 8082 E800 771A 0003 F272 8975 7712 11A4 1182 F310 000B F586 8192 7712 119C EC07 7192 3090 7713 309B 7710 0011 EC03 E58D F074 89C4 F073 88AD 76F8 055A 0000 6884 FFFE 6884 FFF9 F273 8976 6984 0002 76F8 055A 0000 6884 FFFE 7714 09C8 F274 86FB 7713 3090 7713 119C EC07 7093 3090 771A 0003 7712 309B 1182 F272 89AE 7710 0011 6F83 0E00 8193 6FB2 0C9F 1182 F074 89C4 F073 88AD
 *
 * Intent: Flag-gated max-fold with sample fills and dark-call tails. TC = *AR4-live bit 0 (AR4 caller-live,
 * unbound, flagged); bcd delay (orm lane runs, 2 words per oracle) then TC clear joins the 8976 lane
 * (bcd 8976,ntc; delay-first precedent); untaken path runs andm/orm. AR2 = 1370; A = cell;
 * B = A - 5 (sub dual, 71A3 precedent);
 * B >= 0 tail-joins frag_89B3 (bc bgeq; C-bound); else A += 1, cell = A-low (stl), A = 0, BRC = 3. RPTBD lane
 * (RSA = PC+4 per flagged form; delay stm #4516,ar2 runs once): 4x block of B = *AR2, B -= 11, B = max(B,0)
 * (max b signed per 66C5/68A2: A = 0 held), *AR2++ = B-low. AR2 = 4508; 8x mvdk fill of MMR 0x3090
 * (rpt #7). AR3 = 12443; AR0 = 17; 4x mvdd *AR2+ -> *AR3 with AR3 += AR0 (+0% wrap needs BK, flagged). Dark
 * routine_89C4() (call; asm-only span head, forward extern); b-tail frag_88AD (8894 interior, 891C precedent).
 * Words 8990-89B2 sit past the unconditional bd 8976 (delays orm/st run, then jump) with no entries
 * -- dead per 5886, preserved in asm, not modeled. AR4 caller-live, dead after (flagged).
 */
extern void routine_89C4(void); /* joins 89c4_routine_89c4; see docs/evidence/extern-triage.md */
extern void frag_88AD(void); /* joins 8894_frag_8894 interior @+0x19; see docs/evidence/extern-triage.md */
extern void frag_89B3(void);

void frag_8956(int *par4)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int taken;
    int i;


    taken = (*par4 & 1) != 0;                              /* bitf *ar4,#1 */
    *par4 |= 1;                                            /* bcd delay: orm (runs, 2 words) */
    if (!taken)                                            /* bcd 0x8976,ntc */
        goto l8976;
    *par4 &= -7;                                           /* andm (untaken path) */
    *par4 |= 4;                                            /* orm (untaken path) */
    ar2 = (int *)1370;                                     /* stm #1370,ar2 */
    a = (long)*ar2;                                        /* ld *ar2,a */
    b = a - 5;                                             /* sub #5,a,b */
    if (b >= 0) {                                          /* bc 0x89b3,bgeq */
        frag_89B3();
        return;
    }
    a = a + 1;                                             /* add #1,a */
    *ar2 = (int)(a & 0xFFFF);                              /* stl a,*ar2 */
    a = 0;                                                 /* ld #0,a */
    ar2 = (int *)4516;                                     /* rptbd delay: stm (runs once) */
    /* stm #3,brc; rptbd 0x8975 (RSA = PC+4, 4 iters, flagged) */
    for (i = 0; i < 4; i++) {
        b = (long)*ar2;                                    /* ld *ar2,b */
        b = b - 11;                                        /* sub #11,b */
        if (b < a)                                         /* max b (A = 0 held) */
            b = a;
        *ar2++ = (int)(b & 0xFFFF);                         /* stl b,*ar2+ */
    }
l8976:
    ar2 = (int *)4508;                                     /* stm #4508,ar2 */
    for (i = 0; i < 8; i++)                                /* rpt #7 */
        *(volatile int *)0x3090 = *ar2++;                   /* mvdk *ar2+,0x3090 */
    ar3 = (int *)12443;                                    /* stm #12443,ar3 */
    /* stm #17,ar0 (second-rptbd preset; wrap needs BK, flagged) */
    for (i = 0; i < 4; i++) {                               /* rpt #3 */
        *ar3 = *ar2++;                                     /* mvdd *ar2+,*ar3+0% */
        ar3 += 17;                                         /* +0% step (wrap flagged) */
    }
    routine_89C4();                                        /* call 0x89c4 (dark) */
    frag_88AD();                                           /* b 0x88ad (tail) */
    /* dead 8990-89B2 (past unconditional bd, not modeled) */
}
