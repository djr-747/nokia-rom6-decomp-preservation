/* ROM6 0xAF88 LEAF_AF88 -- 9w.
 * Verified encoding: src/rom6/kernel/af88_leaf_af88.asm (recombine MATCH).
 * ORIGIN 0xAF88
 * EXPECT: F074 A2C3 F074 A361 FC44 F274 A2B9 7715 DD8C FC00
 *
 * Intent: Worker pair plus gated primitive. Runs 0xA2C3 then 0xA361; when the 0xA361 result is nonzero (rc aneq on live A, exact skip semantics in the .asm), runs the A2B9 primitive with AR5 preset -8820 (calld delay slot), return.
 */
extern void msg_worker_A2C3(void);
extern int sub_A361(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void leaf_AF88(void)
{
    int **pp5;
    int a;
    msg_worker_A2C3();                           /* call 0xa2c3 */
    a = sub_A361();                              /* call 0xa361 */
    G_AR5 = (int *)-8820;                        /* calld delay slot */
    if (a != 0)                                  /* rc aneq */
        pp5 = &G_AR5;
        msg_primitive_A2B9(&pp5);
        G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
