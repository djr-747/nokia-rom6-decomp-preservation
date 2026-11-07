/* ROM6 0xB062 FRAG_B062 -- 30w.
 * Verified encoding: src/rom6/kernel/b062_frag_b062.asm (recombine MATCH).
 * ORIGIN 0xB062
 * EXPECT: F274 A2B9 7715 DDF4 60F8 2510 00C0 F820 B07B 61F8 051F 1800 F830 B07B 61F8 051C 0003 10F8 2EFE F830 B07B F844 B07B F981 8060 F274 A2B9 7715 DDF9 FC00
 *
 * Intent: Gated lane with shared tail. Same shape as LANE_AFF9 with AR5 presets -8716/-8711 and the shared B07B tail (bytes F274 A2B9 7715 DDF9 FC00, byte-identical to the own tail, cited); all four gates jump there; else far call 0x18060 first.
 */
extern void msg_primitive_A2B9(int ***ppp5);
extern void far_18060(void);

static int *G_AR5;

void frag_B062(void)
{
    int **pp5;
    int a;
    G_AR5 = (int *)-8716;                        /* calld delay slot */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
    if (*(volatile int *)0x2510 != 192)          /* cmpm, bc ntc */
        goto L_TAIL;
    if ((*(volatile int *)0x51F & 6144) != 0)    /* bitf, bc tc */
        goto L_TAIL;
    if ((*(volatile int *)0x51C & 3) != 0)       /* bitf, bc tc */
        goto L_TAIL;
    a = *(volatile int *)0x2EFE;             /* ld */
    if (a != 0)                                  /* bc aneq */
        goto L_TAIL;
    far_18060();                                 /* fcall 0x18060 */
L_TAIL:
    G_AR5 = (int *)-8711;                        /* B07B shared tail */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
}
