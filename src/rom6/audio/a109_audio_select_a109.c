/* ROM6 0xA109 AUDIO_SELECT_A109 -- 34w.
 * Verified encoding: src/rom6/audio/a109_audio_select_a109.asm (recombine MATCH).
 * ORIGIN 0xA109
 * EXPECT: F074 061C 61F8 0577 0420 F820 A12A 11F8 2AEE E80F F180 F84C A126 61F8 2B08 0001 F830 A120 11F8 2AEB F180 F84C A126 56F8 0238 4EF8 023A F073 A12A 56F8 023A 4EF8 0238 FC00
 *
 * Intent: audio path select by status bits. Helper call, then: if
 * bit 10/6 of 0x577 clear, return (bc A12A ntc, A12A is the RET).
 * If (0x2AEE & 15) take the reverse 32-bit copy (A126: 0x23A to
 * 0x238); else if bit 0 of 0x2B08 take the forward copy (A120:
 * 0x238 to 0x23A); else retest 0x2AEB & 15 for the reverse copy.
 * dld/dst move 32-bit cells.
 */
extern void helper_061C(void);

static long dld(int addr) { return ((long)(*(volatile int *)addr) << 16); }
static void dst(long v, int addr) { *(volatile int *)addr = (int)(v >> 16); }

void audio_select_A109(void)
{
    helper_061C();                              /* call 0x61c */
    if (!(*(volatile int *)0x577 & 1056))       /* bitf, bc A12A ntc */
        return;
    if (*(volatile int *)0x2AEE & 15)           /* ld, and #15, bc A126 */
        goto rev;
    if (*(volatile int *)0x2B08 & 1) {          /* bitf, bc A120 tc */
        dst(dld(0x238), 0x23A);                 /* A120 forward copy */
        return;                                 /* b A12A */
    }
    if (*(volatile int *)0x2AEB & 15)           /* bc A126 bneq */
        goto rev;
    dst(dld(0x238), 0x23A);                     /* fall-through forward */
    return;
rev:
    dst(dld(0x23A), 0x238);                     /* A126 reverse copy, ret */
}
