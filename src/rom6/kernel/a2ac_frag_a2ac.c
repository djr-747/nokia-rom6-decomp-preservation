/* ROM6 0xA2AC FRAG_A2AC -- 13w.
 * Verified encoding: src/rom6/kernel/a2ac_frag_a2ac.asm (recombine MATCH).
 * ORIGIN 0xA2AC
 * EXPECT: F074 A2C3 F074 A3A3 FC4C 71F8 022D 265B F274 A2B9 7715 DDB8 FC00
 *
 * Intent: Gated producer step. Runs workers 0xA2C3/0xA3A3; when B is nonzero (rc bneq on B as left by sub_A3A3 -- unverified which op sets it, modeled as live-in), copies cell 0x22D to 0x265B, then the A2B9 primitive with AR5 preset -8776 (calld delay slot), return.
 */
extern void msg_worker_A2C3(void);
extern void sub_A3A3(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_A2AC(int b_live)
{
    int **pp5;
    msg_worker_A2C3();                           /* call 0xa2c3 */
    sub_A3A3();                                  /* call 0xa3a3 */
    if (b_live != 0)                             /* rc bneq */
        *(volatile int *)0x265B =
            *(volatile int *)0x22D;            /* mvdk */
    G_AR5 = (int *)-8776;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
