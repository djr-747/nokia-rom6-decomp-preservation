/* ROM6 0xC7E9 FRAG_C7E9 -- 13w.
 * Verified encoding: src/rom6/kernel/c7e9_frag_c7e9.asm (recombine MATCH). masked compare (DROM lane).
 * ORIGIN 0xC7E9
 * EXPECT: 8086 1185 F330 C600 F030 C600 F520 F84D C7F8 6886 F9FF F073 283D
 * Intent: *AR6-entry = A-live-in (stl a,*ar6). B = *AR5-entry masked with
 * -14848 (0xC600; and, sign-extends via 1185 ld). A &= -14848 (and #-14848,a:
 * A = A & 0xC600). B = B - A (sub a,b). Equal (B == 0) tail-enters dark
 * FRAG_C7F8 (bc beq, forward extern). Else *AR6 &= -1537 (0xF9FF; andm) and
 * tail-enters dark 0x283D (b, forward extern, void per 2867/2875 precedent).
 * A, AR5, AR6 entry-live; B internal.
 * Bound C7E9-C7F5 (exit F073@C7F4->283D + operand C7F5, byte-verified).
 */
extern void frag_C7F8(void);
extern void frag_283D(void);

void frag_C7E9(int a_live, int *par5, int *par6)
{
    long a;
    long b;

    *par6 = a_live;                            /* stl a,*ar6 */
    b = (long)*par5;                           /* ld *ar5,b */
    b &= -14848L;                              /* and #-14848,b (mask 0xC600) */
    a = (long)(a_live & -14848);               /* and #-14848,a */
    b = b - a;                                 /* sub a,b: B = B - A */
    if (b == 0) {                              /* bc 0xc7f8,beq */
        frag_C7F8();
        return;
    }
    *par6 &= -1537;                            /* andm #-1537,*ar6 */
    frag_283D();                               /* b 0x283d tail */
}
