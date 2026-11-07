/* ROM6 0x2E52 FRAG_2E52 -- 18w.
 * Verified encoding: src/rom6/boot/2e52_frag_2e52.asm (recombine MATCH).
 * ORIGIN 0x2E52
 * EXPECT: F074 37D8 61F8 0866 0003 FC20 61F8 2628 4000 F820 2E61 61F8 250F 00D0 FC30 F074 2E64 FC00
 *
 * Intent: Bit-test chain plus call. Runs 0x37D8; TC = any-bit-set (BITF ground truth per ti-c54x op_bitf: TC = ((Smem & lk) != 0)). Chain: test cell 0x866#3, skip next when clear (rc ntc); test cell 0x2628#16384, jump to the call when clear (bc 0x2e61,ntc); test cell 0x250F#208, skip the call when set (rc tc); else call 0x2E64, return.
 */
extern void sub_37D8(void);
extern void sub_2E64(void);

void frag_2E52(void)
{
    int tc;
    sub_37D8();                                  /* call 0x37d8 */
    tc = (*(volatile int *)0x866 & 3) != 0;      /* bitf, rc ntc */
    if (tc)
        tc = (*(volatile int *)0x2628 & 16384) != 0; /* bitf */
    if (!tc)                                     /* bc 0x2e61,ntc */
        goto L_CALL;
    tc = (*(volatile int *)0x250F & 208) != 0;   /* bitf */
    if (tc)                                      /* rc tc */
        return;
L_CALL:
    sub_2E64();                                  /* call 0x2e64 */
    /* ret */
}
