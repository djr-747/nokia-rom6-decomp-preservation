/* ROM6 0x3907 ROUTINE_3907 + FRAG_3913 + SUB_391F -- 49w.
 * Verified encoding: src/rom6/kernel/3907_routine_3907.asm (recombine MATCH).
 * ORIGIN 0x3907
 * EXPECT: F074 391F 11F8 3ED4 FF44 11F8 3E7F 8813 F273 38AA 10F8 0060 F074 391F 11F8 3ED5 FF44 11F8 3E80 8813 F273 38AA 10F8 0060 F110 03CF 7213 0580 FF4A F010 0400 80F8 0060 FA4A 392F F110 007C F495 E800 FD4F E801 61F8 263B 0001 FC20 8093 7313 0580 FC00
 *
 * Intent: Classify-then-select heads over a shared body,
 * three entries (sled convention). The 391F body:
 * B = A-live-in - 975 (sub lk); AR3 = cell 0x580 (mvdm);
 * B negative runs A -= 1024 (xc 2,bgeq covers the 2-word
 * sub); cell 0x60 = A-low (stl); the bcd tests the
 * PRE-delay B (leaf evaluates over input state): both
 * delays always run (B = A - 124, then nop); taken path
 * (B >= 0) runs A = 1, fall path runs A = 0 and B > 0
 * reloads A = 1 (xc 1,bleq covers the 1-word ld);
 * TC = bit 0 of cell 0x263B (bitf); clear returns (rc ntc
 * -- valid mid-gosub: pops to the head caller); else cell
 * AR3 = A-low with AR3 post-incremented, cell 0x580 =
 * AR3, return. The body always returns 0 or 1 (int out).
 * The 3907 head: A-body = body(entry A); B = cell 0x3ED4,
 * body-A zero reloads B = cell 0x3E7F (xc 2,aneq covers
 * the 2-word ld, tests A); AR3 = body-A-low (stlm); the bd
 * delay loads A = cell 0x60, then tail-enters frag_38AA
 * (bd 0x38aa, always taken; the 389C file defines that
 * entry -- A/B/AR2/AR3 threaded, AR3 carrying body-A as
 * its address value per hw) and returns. The 3913 head
 * (externally entered, e.g. 389C's bc; unreachable from
 * the 3907 head past its always-taken bd, noted): same
 * shape on cells 0x3ED5/0x3E80 with its own gosub A.
 * Bound 3907-3937.
 */
extern void frag_38AA(long a_live, long b_live, int *ar2_live, int *ar3_live);

static int sub_391F(long a_live)
{
    int *ar3;
    long a = a_live;
    long b;
    int taken;
    b = a - 975;                                     /* sub #975,a,b */
    ar3 = (int *)*(volatile int *)0x580;             /* mvdm 0x580,ar3 */
    if (b < 0)                                       /* xc 2,bgeq */
        a -= 1024;                                   /* sub #1024,a */
    *(volatile int *)0x60 = (int)(a & 0xFFFF);       /* stl a,*(0x60) */
    taken = (b >= 0);                                /* bcd tests pre-delay B */
    b = a - 124;                                     /* delay-1 (always runs) */
    /* nop (delay-2) */
    if (taken)                                       /* bcd 0x392f,bgeq */
        a = 1;                                       /* ld #1,a */
    else {
        a = 0;                                       /* ld #0,a */
        if (b > 0)                                   /* xc 1,bleq */
            a = 1;                                   /* ld #1,a */
    }
    if ((*(volatile int *)0x263B & 1) == 0)          /* bitf; rc ntc */
        return (int)a;
    *ar3++ = (int)(a & 0xFFFF);                      /* stl a,*ar3+ */
    *(volatile int *)0x580 = (int)ar3;               /* mvmd ar3,0x580 */
    return (int)a;                                    /* ret */
}

void routine_3907(long a_live, int *ar2_in)
{
    long abody;
    long b;
    long a;
    abody = sub_391F(a_live);                        /* call 0x391f */
    b = (long)*(volatile int *)0x3ED4;               /* ld *(0x3ed4),b */
    if (abody == 0)                                  /* xc 2,aneq */
        b = (long)*(volatile int *)0x3E7F;           /* ld *(0x3e7f),b */
    a = (long)*(volatile int *)0x60;                 /* bd delay (runs first) */
    frag_38AA(a, b, ar2_in, (int *)abody);           /* bd 0x38aa (tail) */
}

void frag_3913(long a_live, int *ar2_in)
{
    long abody;
    long b;
    long a;
    abody = sub_391F(a_live);                        /* call 0x391f */
    b = (long)*(volatile int *)0x3ED5;               /* ld *(0x3ed5),b */
    if (abody == 0)                                  /* xc 2,aneq */
        b = (long)*(volatile int *)0x3E80;           /* ld *(0x3e80),b */
    a = (long)*(volatile int *)0x60;                 /* bd delay (runs first) */
    frag_38AA(a, b, ar2_in, (int *)abody);           /* bd 0x38aa (tail) */
}
