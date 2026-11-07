/* ROM6 0xB036 FRAG_B036 -- 21w.
 * Verified encoding: src/rom6/kernel/b036_frag_b036.asm (recombine MATCH).
 * ORIGIN 0xB036
 * EXPECT: 7714 09C8 FB81 A8FD 7713 2F2A F981 A260 F074 A5E1 10F8 2EFE F844 B046 F981 80A7 F274 A2B9 7715 DDDD FC00
 *
 * Intent: Far-call chain with identical-tail branch. AR4 = 2504 feeds far call 0x1A8FD (fcalld, AR3 = 12074 preset in the delay slot, always executes), then far call 0x1A260, then the 0xA5E1 measure setup; nonzero cell 0x2EFE branches to B046 (bc 0xb046,aneq), whose bytes are identical to the own tail (calld 0xa2b9 with AR5 = -8739, return); else far call 0x180A7 first. AR5 preset shared across both paths (executes in its delay slot on either path).
 */
extern void far_1A8FD(void);
extern void far_1A260(void);
extern void meas_setup_A_A5E1(void);
extern void far_180A7(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR3;
static int *G_AR4;
static int *G_AR5;

void frag_B036(void)
{
    int **pp5;
    G_AR4 = (int *)2504;                         /* stm #2504,ar4 */
    G_AR3 = (int *)12074;                        /* fcalld delay slot */
    far_1A8FD();                                 /* fcalld 0x1a8fd */
    far_1A260();                                 /* fcall 0x1a260 */
    meas_setup_A_A5E1();                         /* call 0xa5e1 */
    G_AR5 = (int *)-8739;                        /* shared delay preset */
    if (*(volatile int *)0x2EFE != 0) {          /* ld; bc aneq */
        pp5 = &G_AR5;
        msg_primitive_A2B9(&pp5);
        G_AR5 = *pp5;  /* write back any callee bump */
        return;
    }
    far_180A7();                                 /* fcall 0x180a7 */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
