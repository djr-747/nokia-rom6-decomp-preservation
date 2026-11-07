/* ROM6 0x3028 POST_RETD_3028 -- 23w.
 * Verified encoding: src/rom6/boot/3028_post_retd_3028.asm (recombine MATCH).
 * ORIGIN 0x3028
 * EXPECT: E800 F074 3986 68F8 0552 F7FF 7718 02C1 80F8 054F F074 2E2F 10F8 0871 F110 0000 F84D 303D 8812 F074 226C F073 2000
 *
 * Intent: Post-return setup with far join. A = 0; runs CMD_DISPATCH_PORT15 0x3986 (has .asm, no C yet, forward extern); clears bit 11 of cell 0x552 (andm #-2049); SP = 705 (stack pointer preset, hardware state, cited not bound); A stored to cell 0x54F; calls dispatcher_entry_2E2F (C). A = cell 0x871, B = A - 0, zero jumps away to dark 0x303D (bc beq, forward extern; SUB per op_sub). Else AR2 = A, calls dark 0x226C (forward extern), tail-enters dark 0x2000 (b, forward extern). Bound 3028-303E.
 */
extern void sub_3986(void);
extern void dispatcher_entry_2E2F(void);
extern void frag_303D(void); /* joins 3028_post_retd_3028 interior @+0x15; see docs/evidence/extern-triage.md */
extern void frag_226C(void); /* unowned @0x226C; see docs/evidence/extern-triage.md */
extern void frag_2000(void); /* unowned @0x2000; see docs/evidence/extern-triage.md */

void frag_3028(void)
{
    int a;
    int b;
    a = 0;                                       /* ld #0,a */
    sub_3986();                       /* call 0x3986 */
    *(volatile int *)0x552 &= -2049;         /* andm #-2049 */
    /* stm #705,sp (stack pointer, hardware state) */
    *(volatile int *)0x54F = a;              /* stl a,*(0x54f) */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    a = *(volatile int *)0x871;              /* ld *(0x871),a */
    b = a - 0;                                   /* sub #0,a,b */
    if (b == 0) {                                /* bc 0x303d,beq */
        frag_303D();                             /* away, dark */
        return;
    }
    /* stlm a,ar2 (AR2 = A, flows into the unbound 0x226c call) */
    frag_226C();                                 /* call 0x226c */
    frag_2000();                                 /* b 0x2000 tail */
}
