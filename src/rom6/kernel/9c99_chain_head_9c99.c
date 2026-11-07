/* ROM6 0x9C99 CHAIN_HEAD_9C99 -- 54w gain-apply + dispatch tail.
 * Verified encoding: src/rom6/kernel/9c99_chain_head_9c99.asm (recombine MATCH).
 * ORIGIN 0x9C99
 * EXPECT: F074 06D4 F074 06BE 7712 29C8 10F8 0860 8092 7713 085C 771A 009F F272 9CAB 7713 085C A401 8292 E99F 61F8 0860 0090 F820 9CCF F074 9F35 F274 8BDE 7714 29C9 F074 8C0A F074 9F35 60F8 2F03 0000 68F8 0860 9FFF FF20 69F8 0860 4000 7713 3090 F274 86E3 7714 29C9 E910 F073 9CE7
 *
 * Intent: Runs sub_06D4 (low-zone mini-kernel,
 * unsourced, no trace sighting, flagged) then
 * sub_06BE (low-zone, pchist-evidenced, flagged).
 * AR2 = 10696; A = cell 0x860; *(AR2++) = A-low;
 * AR3 = 2140; BRC = 159. The rptbd delay (AR3 =
 * 2140) runs once, then 160x (BRC + 1): A =
 * *(AR2) x *(AR3) (mpy, 795d form, FRCT doubling
 * dark, flagged); *(AR2++) = A-high (sth). B =
 * 159 (dead after, noted). Bit 4/7 of cell 0x860
 * clear tail-calls frag_9CCF(AR2) and returns
 * (bitf #144; bc ntc). Else runs pooled 9F35
 * (call, no C entry); the calld delay (AR4 =
 * 10697) runs first, then pooled 8BDE (call, no C
 * entry); runs asm-only superblock_8C0A (call,
 * forward extern); runs pooled 9F35 again. TC =
 * (cell 0x2F03 == 0) (cmpm; andm is TC-neutral,
 * required so the xc below tests the cmpm).
 * Cell 0x860 &= -24577 (andm, clears bits 13-14).
 * xc 2,ntc taken runs the orm (cell 0x860 |=
 * 16384) normally; not taken skips the orm head
 * and executes word 0x4000 as an unidentified
 * 1-word opcode (stream re-syncs at the stm;
 * effect unbound, flagged -- byte-verified probe
 * reproduces the image bytes exactly). AR3 =
 * 12432; the calld delay (AR4 = 10697) runs
 * first, then pooled 86E3 (call, no C entry);
 * B = 16; tail-enters frag_9CE7 (b). Out
 * cells/ARs/A/B; entry state all set in-span.
 * EXPECT from the image.
 */
/* call 0x9f35 / calld 0x8bde / calld 0x86e3: pooled, no C entries (see Pool notes) */
extern void sub_06D4(void); /* low-zone mini-kernel, unsourced, flagged */
extern void sub_06BE(void); /* low-zone mini-kernel, pchist-evidenced, flagged */
extern void superblock_8C0A(void); /* asm-only, joins 8c0a_superblock_8c0a */
extern void frag_9CCF(int *ar2_in);
extern void frag_9CE7(void);

void chain_head_9C99(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int i;

    sub_06D4();                                            /* call 0x6d4 */
    sub_06BE();                                            /* call 0x6be */
    ar2 = (int *)(long)10696;                              /* stm #10696,ar2 */
    a = (long)*(volatile int *)0x860;                      /* ld *(0x860),a */
    *ar2++ = (int)(a & 0xFFFFL);                           /* stl a,*ar2+ */
    ar3 = (int *)(long)2140;                               /* stm #2140,ar3 */
    /* stm #159,brc */
    /* rptbd 0x9cab (delay runs once before the block) */
    ar3 = (int *)(long)2140;                               /* delay: stm #2140,ar3 */
    for (i = 0; i < 160; i++) {                            /* rptbd block x (BRC+1) */
        a = (long)*ar2 * *ar3;                             /* mpy *ar2,*ar3,a */
        *ar2++ = (int)((a >> 16) & 0xFFFFL);               /* sth a,*ar2+ */
    }
    b = 159L;                                              /* ld #159,b (dead after) */
    if ((*(volatile int *)0x860 & 144) == 0) {             /* bitf; bc ntc */
        frag_9CCF(ar2);                                    /* b 0x9ccf (tail) */
        return;
    }
    /* call 0x9f35 (pooled; effects dark, flagged) */
    /* calld 0x8bde (delay stm #10697,ar4 runs first) */
    ar4 = (int *)(long)10697;
    /* calld 0x8bde (pooled; effects dark, flagged) */
    superblock_8C0A();                                     /* call 0x8c0a */
    /* call 0x9f35 (pooled) */
    *(volatile int *)0x860 &= -24577;                      /* andm (TC-neutral) */
    if (*(volatile int *)0x2F03 == 0) {                    /* xc 2,ntc not taken */
        /* skip orm head; word 0x4000 runs as an unidentified 1-word opcode
           (stream re-syncs; effect unbound, flagged) */
    } else {
        *(volatile int *)0x860 |= 16384;                   /* orm #16384 (taken) */
    }
    ar3 = (int *)(long)12432;                              /* stm #12432,ar3 */
    /* calld 0x86e3 (delay stm #10697,ar4 runs first) */
    ar4 = (int *)(long)10697;
    /* calld 0x86e3 (pooled; effects dark, flagged) */
    b = 16L;                                               /* ld #16,b */
    frag_9CE7();                                           /* b 0x9ce7 (tail) */
}
