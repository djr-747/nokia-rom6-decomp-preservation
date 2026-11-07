/* ROM6 0xB050 FRAG_B050 -- 18w.
 * Verified encoding: src/rom6/kernel/b050_frag_b050.asm (recombine MATCH).
 * ORIGIN 0xB050
 * EXPECT: F074 067A F074 A2C3 F074 A361 FC44 F074 A4DE F074 A482 F944 A815 F274 A2B9 7715 DDEF FC00
 *
 * Intent: Worker chain with live gate. Runs 0x67A, 0xA2C3, 0xA361; nonzero A361 result runs 0xA4DE (rc aneq), then 0xA482. The cc 0xa815,aneq always fires: the A4DE tail (ld #1,b, verified bytes in a4de_msg_setup_c.asm) leaves B = 1, so sub_A815 runs unconditionally with this citation. Then the A2B9 primitive with AR5 preset -8721 (calld delay slot), return.
 */
extern void sub_067A(void);
extern void msg_worker_A2C3(void);
extern int sub_A361(void);
extern void msg_setup_C_A4DE(void);
extern void msg_setup_A_A482(void);
extern void sub_A815(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_B050(void)
{
    int **pp5;
    sub_067A();                                  /* call 0x67a */
    msg_worker_A2C3();                           /* call 0xa2c3 */
    if (sub_A361() != 0)                         /* call 0xa361; rc aneq */
        msg_setup_C_A4DE();                      /* call 0xa4de; B = 1 */
    msg_setup_A_A482();                          /* call 0xa482 */
    sub_A815();                                  /* cc aneq: B = 1, always */
    G_AR5 = (int *)-8721;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
