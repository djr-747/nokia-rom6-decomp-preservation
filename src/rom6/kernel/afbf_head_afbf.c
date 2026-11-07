/* ROM6 0xAFBF HEAD_AFBF -- 20w.
 * Verified encoding: src/rom6/kernel/afbf_head_afbf.asm (recombine MATCH).
 * ORIGIN 0xAFBF
 * EXPECT: F074 0678 F074 A2C3 71F8 022D 265B F074 A3C5 F074 A3E1 F074 A4DE F94D A815 F274 A2B9 7715 DDC8 FC00
 *
 * Intent: Worker chain with dead gate. Runs 0x678, 0xA2C3, copies cell 0x22D to 0x265B, then 0xA3C5, 0xA3E1, 0xA4DE. The cc 0xa815,beq never fires: the A4DE tail (ld #1,b, verified bytes in a4de_msg_setup_c.asm) leaves B = 1, so the call is omitted with this citation. Then the A2B9 primitive with AR5 preset -8760 (calld delay slot), return.
 */
extern void sub_0678(void);
extern void msg_worker_A2C3(void);
extern void routine_A3C5(void);
extern void routine_A3E1(void);
extern void msg_setup_C_A4DE(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void head_AFBF(void)
{
    int **pp5;
    sub_0678();                                  /* call 0x678 */
    msg_worker_A2C3();                           /* call 0xa2c3 */
    *(volatile int *)0x265B =
        *(volatile int *)0x22D;                /* mvdk */
    routine_A3C5();                              /* call 0xa3c5 */
    routine_A3E1();                              /* call 0xa3e1 */
    msg_setup_C_A4DE();                          /* call 0xa4de; B = 1 */
    /* cc 0xa815,beq dead: B = 1 per A4DE tail */
    G_AR5 = (int *)-8760;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    /* ret */
}
