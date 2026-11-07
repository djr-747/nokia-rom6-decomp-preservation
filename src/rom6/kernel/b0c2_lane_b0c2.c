/* ROM6 0xB0C2 LANE_B0C2 -- 38w guarded dispatch lane.
 * Verified encoding: src/rom6/kernel/b0c2_lane_b0c2.asm (recombine MATCH).
 * ORIGIN 0xB0C2
 * EXPECT: F074 067A F074 A2C3 F074 A361 FC44 F074 A4DE F074 A482 F845 B0F0 F074 A8BF 60F8 2510 00C0 F820 B0F0 F981 A839 F981 A425 61F8 051F 1800 F830 B0E4 61F8 051C 0003 F820 B0E8 F074 A87F F073 B0F0
 *
 * Intent: Setup calls sub_067A (low-zone unsourced, flagged),
 * MSG_WORKER_A2C3, STUB_A361; return if A != 0 (rc aneq,
 * immediate; A callee-defined, dark, flagged); call
 * MSG_SETUP_C, MSG_SETUP_A; A == 0 exits to the B0F0 tail
 * (bc aeq; next span owns). Else call WRAP_A8BF; cell
 * *(0x2510) != 192 exits to B0F0 (cmpm equality, oracle
 * op_cmpm_smem_lk); far_1A839 + far_1A425 (uploaded XPC
 * pages, off-image, extern-triage). Cell *(0x51F) with bits
 * 11-12 set joins the call-WRAP_A87F lane directly (bc
 * 0xb0e4,tc; bitf any-bit TC, oracle op_bitf_smem_lk); else
 * cell *(0x51C) with bits 0-1 clear exits to B0E8 (bc ntc;
 * next span owns), set falls to WRAP_A87F, then the B0F0
 * tail (b; next span owns).
 * EXPECT from the image.
 */
extern void far_1A839(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void far_1A425(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */

void lane_B0C2(void)
{
    long a;  /* defined by callees (dark, flagged) */

    sub_067A();                                              /* call 0x67a (low-zone, flagged) */
    msg_worker_A2C3();                                       /* call 0xa2c3 */
    stub_A361();                                             /* call 0xa361 */
    if (a != 0)                                              /* rc aneq (immediate) */
        return;
    msg_setup_C();                                           /* call 0xa4de */
    msg_setup_A_A482();                                      /* call 0xa482 */
    if (a == 0)                                              /* bc 0xb0f0,aeq (next span owns) */
        return;
    wrap_A8BF();                                             /* call 0xa8bf */
    if (*(volatile int *)0x2510 != 192)                      /* cmpm, bc ntc */
        return;
    far_1A839();                                             /* fcall 0x1a839 */
    far_1A425();                                             /* fcall 0x1a425 */
    if ((*(volatile int *)0x51F & 6144) == 0) {              /* bitf, bc 0xb0e4,tc */
        if ((*(volatile int *)0x51C & 3) == 0)               /* bitf, bc 0xb0e8,ntc */
            return;                                          /* b0e8 (next span owns) */
    }
    wrap_A87F();                                             /* call 0xa87f (@b0e4 join + fall-through) */
    /* b 0xb0f0 (next span owns) */
}
