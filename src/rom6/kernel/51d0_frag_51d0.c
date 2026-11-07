/* ROM6 0x51D0 FRAG_51D0 -- 8w.
 * Verified encoding: src/rom6/kernel/51d0_frag_51d0.asm (recombine MATCH).
 * ORIGIN 0x51D0
 * EXPECT: 10F8 0374 F845 51CC 6984 0100 1184 FC00
 *
 * Intent: Cell test plus OR-accumulate. A = cell 0x374; when zero (bc 0x51cc,aeq) tail-calls HIT_51CC (B = 0 with the andm #-257 delay stroke clearing bit 8 of *AR4 -- previously inlined here without the stroke, corrected). Else tail-calls the in-span miss sink: sets bit 8 of *AR4 (live-in, orm #256), B = *AR4, returns. Sled: two entry functions, one EXPECT over 51D0-51D7.
 */
extern int hit_51CC(int *par4);

int miss_sink_51D4(int *par4)
{
    *par4 |= 256;                               /* orm #256,*ar4 */
    return *par4;                               /* ld *ar4,b; ret */
}

int frag_51D0(int *par4)
{
    int a = *(volatile int *)0x374;               /* ld *(0x374),a */
    if (a == 0)                                  /* bc 0x51cc,aeq */
        return hit_51CC(par4);
    return miss_sink_51D4(par4);                  /* fall to 51D4 */
}
