/* ROM6 0xB017 LANE_B017 -- 31w (post-RET head).
 * Verified encoding: src/rom6/kernel/b017_lane_b017.asm (recombine MATCH).
 * ORIGIN 0xB017
 * EXPECT: F074 0678 F074 A2C3 F074 A8BF 60F8 2510 00C0 F820 B032 F981 A839 F981 A425 61F8 051F 1800 F830 B030 61F8 051C 0003 F820 B036 F074 A87F F074 A5E1 F073 B046
 *
 * Intent: Mode dispatch lane. Runs dark SUB_0678, MSG_WORKER_A2C3
 * (C: msg_worker_A2C3), then WRAP_A8BF with entry B (C:
 * wrap_A8BF; B threads through the dark calls, clobber risk
 * flagged). cell0x2510 != 192 tail-enters dark 0xB032 (cmpm
 * equality per op_cmpm_smem_lk, 3691 precedent); runs far SUB_1A839
 * + SUB_1A425 (fcall modeled as call, segment crossing flagged);
 * cell0x51F & 6144 set tail-enters dark 0xB030; cell0x51C & 3 clear
 * tail-enters FRAG_B036 (C: frag_B036); else runs WRAP_A87F (C:
 * wrap_A87F) + dark SUB_A5E1, tail-branches dark 0xB046.
 * Bound B017-B035.
 */
extern void sub_0678(void);
extern void msg_worker_A2C3(void);
extern void wrap_A8BF(int b_live);
extern void frag_B032(void);
extern void sub_1A839(void);
extern void sub_1A425(void);
extern void frag_B030(void);
extern void frag_B036(void);
extern void wrap_A87F(void);
extern void sub_A5E1(void);
extern void frag_B046(void);

void lane_B017(int b_live)
{
    int tc;
    sub_0678();                                      /* call 0x678 (dark) */
    msg_worker_A2C3();                               /* call 0xa2c3 */
    wrap_A8BF(b_live);                               /* call 0xa8bf (B clobber risk, flagged) */
    tc = (*(volatile int *)0x2510 == 192);           /* cmpm *(0x2510),#192 */
    if (!tc) {                                       /* bc 0xb032,ntc */
        frag_B032();
        return;
    }
    sub_1A839();                                     /* fcall 0x1a839 */
    sub_1A425();                                     /* fcall 0x1a425 */
    tc = (*(volatile int *)0x51F & 6144) != 0;       /* bitf *(0x51f),#6144 */
    if (tc) {                                        /* bc 0xb030,tc */
        frag_B030();
        return;
    }
    tc = (*(volatile int *)0x51C & 3) != 0;          /* bitf *(0x51c),#3 */
    if (!tc) {                                       /* bc 0xb036,ntc */
        frag_B036();
        return;
    }
    wrap_A87F();                                     /* call 0xa87f */
    sub_A5E1();                                      /* call 0xa5e1 (dark) */
    frag_B046();                                     /* b 0xb046 */
}
