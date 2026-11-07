/* ROM6 0x4B9A FRAG_4B9A -- 14w.
 * Verified encoding: src/rom6/kernel/4b9a_frag_4b9a.asm (recombine MATCH).
 * ORIGIN 0x4B9A
 * EXPECT: 6892 1FFF 771A 0009 F072 4BA5 944D 1A82 8092 6F82 0C5D 8092 F7B8 FC00
 *
 * Intent: Field-merge loop. Clears low 13 bits at live-in *AR2++ (andm #8191); 10 iterations (BRC = 9, rptb 0x4ba5 over ld/or/stl/ld/stl): A = *AR2-- << 13, A |= *AR2, store, A = *AR2 >> 3 (SXM state on entry unknown, flagged; ssbx forces SXM on after the loop), store. AR2 advances one per iteration. SXM set (hardware state, no C form); return.
 */
void frag_4B9A(int **ppar2)
{
    int i;
    int *ar2 = *ppar2;
    *ar2++ &= 8191;                              /* andm #8191,*ar2+ */
    for (i = 0; i < 10; i++) {                   /* stm #9,brc; rptb */
        long a = ((long)*ar2-- << 13);           /* ld *ar2-,13,a */
        a |= (unsigned short)*ar2;                /* or *ar2,a (Smem zero-ext) */
        *ar2++ = (int)a;                         /* stl a,*ar2+ */
        a = *ar2 >> 3;                           /* ld *ar2,-3,a (SXM?) */
        *ar2++ = (int)a;                         /* stl a,*ar2+ */
    }
    /* ssbx st1,sxm: SXM on (hardware state, no C form) */
    *ppar2 = ar2;
    /* ret */
}
