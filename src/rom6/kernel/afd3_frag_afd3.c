/* ROM6 0xAFD3 FRAG_AFD3 -- 38w guarded dispatch lane.
 * Verified encoding: src/rom6/kernel/afd3_frag_afd3.asm (recombine MATCH).
 * ORIGIN 0xAFD3
 * EXPECT: F074 0678 F074 A2C3 F074 A5E1 60F8 2510 00C0 F820 AFF4 61F8 051F 1800 F830 AFF4 61F8 051C 0003 F830 AFF4 10F8 2EFE F844 AFF4 F074 A8D4 F074 9DF4 F981 8019 F981 8040 F074 A7B7 F074 A7EB FC00
 *
 * Intent: Setup calls sub_0678 (low-zone unsourced, flagged),
 * MSG_WORKER_A2C3, MEAS_SETUP_A; then a four-guard chain
 * sharing the AFF4 tail (call AUDIO_A, call AUDIO_B, return):
 * cell *(0x2510) == 192 (cmpm equality, TC per oracle
 * op_cmpm_smem_lk; bc ntc exits on mismatch), cell *(0x51F)
 * has none of bits 11-12 (bitf any-bit TC, oracle
 * op_bitf_smem_lk), cell *(0x51C) has none of bits 0-1, and
 * A = *(0x2EFE) sign-extended (ld, SXM dark, flagged) == 0
 * (bc aneq exits on nonzero). All guards pass: call
 * DISPATCH_A8D4, LEAF_9DF4, far_18019 + far_18040 (uploaded
 * XPC pages, off-image, extern-triage), then the shared
 * tail. A entry dark; out A.
 * EXPECT from the image.
 */
extern void far_18019(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void far_18040(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */

void frag_AFD3(void)
{
    long a;  /* clobbered (entry dark) */

    sub_0678();                                              /* call 0x678 (low-zone, flagged) */
    msg_worker_A2C3();                                       /* call 0xa2c3 */
    meas_setup_A();                                          /* call 0xa5e1 */
    if ((*(volatile int *)0x2510 == 192) &&                  /* cmpm, bc ntc */
        ((*(volatile int *)0x51F & 6144) == 0) &&            /* bitf, bc tc */
        ((*(volatile int *)0x51C & 3) == 0)) {               /* bitf, bc tc */
        a = (long)*(volatile int *)0x2EFE;                   /* ld *(0x2efe),a (SXM dark, flagged) */
        if (a == 0) {                                        /* bc 0xaff4,aneq */
            dispatch_A8D4();                                 /* call 0xa8d4 */
            leaf_9DF4();                                     /* call 0x9df4 */
            far_18019();                                     /* fcall 0x18019 */
            far_18040();                                     /* fcall 0x18040 */
        }
    }
    audio_A_A7B7();                                          /* call 0xa7b7 (shared tail @aff4) */
    audio_B_A7EB();                                          /* call 0xa7eb */
    /* ret */
}
