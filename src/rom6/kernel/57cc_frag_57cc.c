/* ROM6 0x57CC FRAG_57CC -- 50w shared tail, six entries, one EXPECT.
 * Verified encoding: src/rom6/kernel/57cc_frag_57cc.asm (recombine MATCH).
 * ORIGIN 0x57CC
 * EXPECT: 76F8 2EFF 0001 F273 57F4 F340 0004 11F8 2628 60F8 250F 002F F830 57DE 60F8 250F 0022 FC20 10F8 0918 F010 0034 F845 57EE FC43 F010 0007 F845 57F2 FC46 F273 57F4 F340 0004 F273 57F4 F340 000C F340 0014 60F8 2510 00B1 FE20 81F8 2628 68F8 2628 FFE7 FC00
 *
 * Intent: Lane-2 classifier plus shared commit tail for SUB_57A3 (all
 * entries branch- or fall-through-entered from the 57A3 head: bc
 * F820@57AC -> 57D3, bd F273@57C8 -> 57F4, bc F845@57BC -> 57EE,
 * bc F845@57C1 -> 57CC, bc F845@57C5 -> 57F2). B-out throughout.
 * FRAG_57D3: B = state cell 0x2628 (ld); TC = (id 0x250F == 47)
 * (cmpm); match runs FRAG_57DE (bc tc); else TC = (id == 34), mismatch
 * returns B (rc ntc; RC 1-word, not-taken falls through per op_rc),
 * match falls into 57DE. FRAG_57DE: A = cell 0x918 - 52 (sub #52,a);
 * zero (cell == 52) takes the 57EE entry (bc aeq); negative returns B
 * (rc alt); A -= 7, zero (cell == 59) takes the 57F2 entry (bc aeq);
 * positive returns B (rc agt); else B |= 4 in the bd delay slot (always
 * executes) and control takes the 57F4 entry (bd). FRAG_57CC: flag cell
 * 0x2EFF = 1 (st #lk,Smem), then the 57F4 path with B |= 4 (bd delay).
 * FRAG_57EE/57F2: the 57F4 path with B |= 12 (bd delay or #12) /
 * B |= 20 (or #20 fallthrough). FRAG_57F4 commit: TC = (cell 0x2510 ==
 * 177) (cmpm); cell 0x2628 = B-low always (rcd delay slot stl b;
 * RCD executes 2 delay words per op_rcd/a4de); mismatch returns
 * (rcd ntc); match masks cell 0x2628 &= -25 (andm) and returns B (ret).
 * Bound 57CC-57FD (exit FC00@57FD).
 */

int frag_57F4(int b_live)
{
    long b = b_live;
    int tc = (*(volatile int *)0x2510 == 177);    /* cmpm */

    *(volatile int *)0x2628 = (int)(b & 0xFFFF); /* rcd delay: stl */
    if (!tc)                                     /* rcd ntc */
        return (int)b;
    *(volatile int *)0x2628 &= -25;              /* andm #-25 */
    return (int)b;                               /* ret */
}

int frag_57EE(int b_live)
{
    return frag_57F4(b_live | 12);      /* bd delay or #12,b; bd 57f4 */
}

int frag_57F2(int b_live)
{
    return frag_57F4(b_live | 20);               /* or #20,b; to 57f4 */
}

int frag_57CC(int b_live)
{
    *(volatile int *)0x2EFF = 1;                 /* st #1,*(0x2eff) */
    return frag_57F4(b_live | 4);       /* bd delay or #4,b; bd 57f4 */
}

int frag_57DE(int b_live)
{
    long a = *(volatile int *)0x918;             /* ld */
    long b = b_live;

    a -= 52;                                     /* sub #52,a */
    if (a == 0)                                  /* bc 0x57ee,aeq */
        return frag_57EE((int)b);
    if (a < 0)                                   /* rc alt */
        return (int)b;
    a -= 7;                                      /* sub #7,a */
    if (a == 0)                                  /* bc 0x57f2,aeq */
        return frag_57F2((int)b);
    if (a > 0)                                   /* rc agt */
        return (int)b;
    b |= 4;                               /* bd delay slot, always */
    return frag_57F4((int)b);                          /* bd 0x57f4 */
}

int frag_57D3(void)
{
    long b = *(volatile int *)0x2628;            /* ld */
    int tc = (*(volatile int *)0x250F == 47);    /* cmpm */

    if (tc)                                      /* bc 0x57de,tc */
        return frag_57DE((int)b);
    tc = (*(volatile int *)0x250F == 34);        /* cmpm */
    if (!tc)                                     /* rc ntc */
        return (int)b;
    return frag_57DE((int)b);                    /* fall into 57de */
}
