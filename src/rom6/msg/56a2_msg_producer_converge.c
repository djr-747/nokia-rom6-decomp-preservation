/* ROM6 0x56A2 MSG_PRODUCER_CONVERGE -- 21w.
 * Verified encoding: src/rom6/msg/56a2_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x56A2
 * EXPECT: 61F8 3EC8 0010 F820 56B0 E889 11F8 0589 F330 8000 F3F9 F2A0 8812 FF20 7712 0089 F274 2D5E 7713 086D FC00
 *
 * Intent: Producer converge gate. TC = bit 4 of cell 0x3EC8 set (bitf any-bit TC per ti-c54x op_bitf); clear jumps into the xc block at 0x56B0 (bc 0x56b0,ntc): AR2 = 137, AR3 = 2157 (calld delay slot, executes first), call 0x2D5E, return. Set path: A = 137 OR ((cell 0x589 AND 0x8000) logically right-shifted 7 (sftl is the logical barrel shift, zero fill, unlike arithmetic sfta)); AR2 = A; xc skips the preset-plus-call (ntc false... TC set so both skipped, exact); AR3 = 2157 (calld delay slot position, executes as normal insn); return.
 */
extern void sub_2D5E(int *par2, int *par3);

static int *G_AR2;
static int *G_AR3;

void msg_producer_converge_56A2(void)
{
    int tc = (*(volatile int *)0x3EC8 & 16) != 0;   /* bitf */
    if (!tc) {                                     /* bc 0x56b0,ntc */
        G_AR2 = (int *)137;                        /* stm #137,ar2 */
        G_AR3 = (int *)2157;                       /* calld delay slot */
        sub_2D5E(G_AR2, G_AR3);                    /* calld 0x2d5e */
        return;
    }
    {
        int a = 137;                               /* ld #137,a */
        int b = *(volatile int *)0x589 & 0x8000; /* ld, and */
        b = (int)((unsigned)b >> 7);              /* sftl b,-7 (logical) */
        a |= b;                                    /* or b,a */
        G_AR2 = (int *)a;                          /* stlm a,ar2 */
    }
    /* xc 2,ntc: TC set, preset plus call skipped */
    G_AR3 = (int *)2157;                           /* stm (slot pos) */
    /* ret */
}
