/* ROM6 0xAA69 FRAG_AA69 -- 19w.
 * Verified encoding: src/rom6/kernel/aa69_frag_aa69.asm (recombine MATCH).
 * ORIGIN 0xAA69
 * EXPECT: F074 0688 61F8 263A 0200 FC30 10F8 0B67 FC44 61F8 051C 0003 FC30 E802 F274 D0BE 80F8 0ECC FC00
 *
 * Intent: Bit-test chain plus far store. Same chain as FRAG_AA56 with A = 2 stored to cell 0xECC in the calld delay slot (executes before sub_D0BE takes effect), call 0xD0BE, return.
 */
extern void sub_0688(void);
extern void sub_CF25(void);
extern void sub_CF4B(void);
extern void sub_D0BE(void);

void frag_AA69(void)
{
    sub_0688();                                  /* call 0x688 */
    if ((*(volatile int *)0x263A & 512) != 0)    /* bitf, rc tc */
        goto L_CF4B;
    if (*(volatile int *)0xB67 != 0)             /* ld, rc aneq */
        goto L_CF4B;
    if ((*(volatile int *)0x51C & 3) != 0)       /* bitf, rc tc */
        goto L_CF4B;
    sub_CF25();                                  /* call 0xcf25 */
L_CF4B:
    sub_CF4B();                                  /* call 0xcf4b */
    *(volatile int *)0xECC = 2;              /* calld delay slot */
    sub_D0BE();                                  /* calld 0xd0be */
    /* ret */
}
