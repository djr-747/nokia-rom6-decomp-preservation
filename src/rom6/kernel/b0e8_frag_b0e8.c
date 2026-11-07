/* ROM6 0xB0E8 FRAG_B0E8 -- 13w.
 * Verified encoding: src/rom6/kernel/b0e8_frag_b0e8.asm (recombine MATCH).
 * ORIGIN 0xB0E8
 * EXPECT: 7714 09C8 FB81 A8FD 7713 2F2A F981 A260 F274 A2B9 7715 DE0E FC00
 *
 * Intent: Far-call pair plus primitive. AR4 = 2504 feeds far call 0x1A8FD (fcalld, AR3 = 12074 preset in the delay slot, always executes), then far call 0x1A260, then the A2B9 primitive with AR5 preset -8690 (calld delay slot), return.
 */
extern void far_1A8FD(void);
extern void far_1A260(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR3;
static int *G_AR4;
static int *G_AR5;

void frag_B0E8(void)
{
    int **pp5;
    G_AR4 = (int *)2504;                         /* stm #2504,ar4 */
    G_AR3 = (int *)12074;                        /* fcalld delay slot */
    far_1A8FD();                                 /* fcalld 0x1a8fd */
    far_1A260();                                 /* fcall 0x1a260 */
    G_AR5 = (int *)-8690;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
