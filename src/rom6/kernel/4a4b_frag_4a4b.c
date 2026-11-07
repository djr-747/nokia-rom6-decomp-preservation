/* ROM6 0x4A4B FRAG_4A4B -- 24w.
 * Verified encoding: src/rom6/kernel/4a4b_frag_4a4b.asm (recombine MATCH).
 * ORIGIN 0x4A4B
 * EXPECT: 60F8 250F 0022 F820 4A7B 60F8 34BF 0003 F820 4A6B 6FF8 366F 0E20 F845 4A63 6FF8 37B0 0E20 F845 4A67 F273 4AE0 7685 0003
 *
 * Intent: Dual-subtract select with delayed tail. Cell 0x250F != 34 runs dark 0x4A7B (bc ntc, forward extern); cell 0x34BF != 3 runs dark 0x4A6B (bc ntc). A = B-live-in minus *(0x366f) (SUB Xmem,src,dst form: dst = (src << 0) - Xmem; B threaded as int param, 40-bit narrowing noted per ALT precedent), zero runs unbound FRAG_4A63 (bc aeq, has .asm, forward extern void: its 0x4A63 entry path overwrites A then branches out before any B/AR use). A = B minus *(0x37B0), zero runs dark 0x4A67 (bc aeq). Else delayed-branch into C FRAG_4AE0 (bd, C-bound with AR5) with *AR5-entry = 3 in the delay slot (always runs, visible to the callee per 2A73). Bound 4A4B-4A62.
 */
extern void frag_4A7B(void);
extern void frag_4A6B(void);
extern void frag_4A63(void);
extern void frag_4A67(void);
extern void frag_4AE0(int *par5);

void frag_4A4B(int b_live, int *par5)
{
    int a;
    int b = b_live;
    if (*(volatile int *)0x250F != 34) {       /* cmpm, bc ntc */
        frag_4A7B();                                /* away, dark */
        return;
    }
    if (*(volatile int *)0x34BF != 3) {         /* cmpm, bc ntc */
        frag_4A6B();                                /* away, dark */
        return;
    }
    a = b - *(volatile int *)0x366F;           /* sub *(0x366f),b,a */
    if (a == 0) {                                  /* bc 0x4a63,aeq */
        frag_4A63();                               /* away, unbound C */
        return;
    }
    a = b - *(volatile int *)0x37B0;           /* sub *(0x37b0),b,a */
    if (a == 0) {                                  /* bc 0x4a67,aeq */
        frag_4A67();                               /* away, dark */
        return;
    }
    *par5 = 3;                                     /* st #3,*ar5 (bd slot) */
    frag_4AE0(par5);                               /* bd 0x4ae0 tail */
}
