/* ROM6 0xB14B FRAG_B14B -- 12w.
 * Verified encoding: src/rom6/kernel/b14b_frag_b14b.asm (recombine MATCH).
 * ORIGIN 0xB14B
 * EXPECT: F274 A2B9 7715 DE34 76F8 09C6 0000 F274 A2B9 7715 DE3F FC00
 *
 * Intent: Twin primitive with cell clear. First A2B9 primitive (AR5 preset -8652, calld delay slot), clears cell 0x9C6, then the second primitive (AR5 preset -8641), return.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_B14B(void)
{
    int **pp5;
    G_AR5 = (int *)-8652;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    *(volatile int *)0x9C6 = 0;              /* st #0,*(0x9c6) */
    G_AR5 = (int *)-8641;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
