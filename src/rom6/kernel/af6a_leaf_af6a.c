/* ROM6 0xAF6A LEAF_AF6A -- 9w.
 * Verified encoding: src/rom6/kernel/af6a_leaf_af6a.asm (recombine MATCH).
 * ORIGIN 0xAF6A
 * EXPECT: F074 A2C3 71F8 022D 265B F274 A2B9 7715 DD4F FC00
 *
 * Intent: Producer step. Runs worker 0xA2C3, copies cell 0x22D to 0x265B (mvdk, unconditional here unlike the rc-gated A269 site), then the A2B9 primitive with AR5 preset -8881 (calld delay slot), return.
 */
extern void msg_worker_A2C3(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void leaf_AF6A(void)
{
    int **pp5;
    msg_worker_A2C3();                           /* call 0xa2c3 */
    *(volatile int *)0x265B =
        *(volatile int *)0x22D;                /* mvdk */
    G_AR5 = (int *)-8881;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
