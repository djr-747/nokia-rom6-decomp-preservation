/* ROM6 0xAFF9 LANE_AFF9 -- 30w.
 * Verified encoding: src/rom6/kernel/aff9_lane_aff9.asm (recombine MATCH).
 * ORIGIN 0xAFF9
 * EXPECT: F274 A2B9 7715 DDD1 60F8 2510 00C0 F820 B012 61F8 051F 1800 F830 B012 61F8 051C 0003 10F8 2EFE F830 B012 F844 B012 F981 8060 F274 A2B9 7715 DDD6 FC00
 *
 * Intent: Gated lane with shared tail. A2B9 primitive with AR5 preset -8751 (calld delay slot); cell 0x2510 != 192 jumps to the shared B012 tail (bc ntc); bits 12-13 of cell 0x51F set jumps there too (bc tc); bit 0-1 of cell 0x51C set jumps there too (bc tc); A = cell 0x2EFE, nonzero jumps there (bc aneq); else far call 0x18060. All taken paths land on the B012 bytes (calld 0xa2b9 with AR5 = -8746, return: byte-identical to the own tail, cited); fall-through runs it too. BITF any-bit TC per ti-c54x op_bitf; CMPM TC-on-equal per ti-c54x op_cmpm.
 */
extern void msg_primitive_A2B9(int ***ppp5);
extern void far_18060(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */

static int *G_AR5;

void lane_AFF9(void)
{
    int **pp5;
    int a;
    G_AR5 = (int *)-8751;                        /* calld delay slot */
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
    G_AR5 = (int *)-8746;                        /* B012 shared tail */
    pp5 = &G_AR5;
    msg_primitive_A2B9(&pp5);
    G_AR5 = *pp5;  /* write back any callee bump */
}
