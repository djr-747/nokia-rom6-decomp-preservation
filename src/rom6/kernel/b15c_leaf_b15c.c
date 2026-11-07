/* ROM6 0xB15C LEAF_B15C -- 16w.
 * Verified encoding: src/rom6/kernel/b15c_leaf_b15c.asm (recombine MATCH).
 * ORIGIN 0xB15C
 * EXPECT: F074 A2C3 F074 A361 FC44 F074 A4DE F074 A482 F944 A91C F274 A2B9 7715 DE4F FC00
 *
 * Intent: Worker chain with live gate. Runs 0xA2C3 then 0xA361; nonzero A361 result runs 0xA4DE (rc aneq), then 0xA482. The cc 0xa91c,aneq always fires: the A4DE tail (ld #1,b, verified bytes in a4de_msg_setup_c.asm) leaves B = 1, so sub_A91C runs unconditionally with this citation. Then the A2B9 primitive with AR5 preset -8625 (calld delay slot), return.
 */
extern void msg_worker_A2C3(void);
extern int sub_A361(void); /* joins a361_stub_a361; see docs/evidence/extern-triage.md */
extern void msg_setup_C(void);
extern void msg_setup_A_A482(void); /* joins a482_msg_setup_a; see docs/evidence/extern-triage.md */
extern void sub_A91C(void); /* joins a91c_routine_a91c; see docs/evidence/extern-triage.md */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void leaf_B15C(void)
{
    int **pp5;
    msg_worker_A2C3();                           /* call 0xa2c3 */
    if (sub_A361() != 0)                         /* call 0xa361; rc aneq */
        msg_setup_C();                      /* call 0xa4de; B = 1 */
    msg_setup_A_A482();                          /* call 0xa482 */
    sub_A91C();                                  /* cc aneq: B = 1, always */
    G_AR5 = (int *)-8625;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
