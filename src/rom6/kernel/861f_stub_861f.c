/* ROM6 0x861F STUB_861F -- 8w.
 * Verified encoding: src/rom6/kernel/861f_stub_861f.asm (recombine MATCH).
 * ORIGIN 0x861F
 * EXPECT: 6D8A 56F8 0060 F074 8627 4EF8 0060 FC00
 *
 * Intent: 32-bit cell transform stub. AR2-- (mar); A = 32-bit *(0x60)
 * (dld absolute, 2a8a precedent); run dark SUB_8627 (forward extern,
 * asm-only); *(0x60) = A 32-bit (dst absolute, 2a8a precedent); return.
 * AR2 caller-live, never set in-span (unbound local, flagged); zero
 * callers (entry ambiguous -- calls land on the ret word 861E per prior
 * pool note; stub may be unreachable, flagged).
 */
extern void sub_8627(void); /* joins 8627_sub_8627; see docs/evidence/extern-triage.md */

void stub_861F(void)
{
    long a;
    int *ar2;      /* caller-live, never set in-span (flagged) */

    ar2--;                                                 /* mar *ar2- */
    a = ((long)*(volatile int *)0x60 << 16) |              /* dld *(0x60),a */
        ((unsigned)*(volatile int *)0x61 & 0xFFFF);
    sub_8627();                                            /* call 0x8627 */
    *(volatile int *)0x60 = (int)((a >> 16) & 0xFFFF);     /* dst (high) */
    *(volatile int *)0x61 = (int)(a & 0xFFFF);              /* dst (low) */
    /* ret */
}
