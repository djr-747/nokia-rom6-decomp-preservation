/* ROM6 0x4D9D SUB_4D9D -- 10w.
 * Verified encoding: src/rom6/kernel/4d9d_sub_4d9d.asm (recombine MATCH).
 * ORIGIN 0x4D9D
 * EXPECT: F272 4DA4 7712 2F80 1292 718A 0009 8492 6D8A FC00
 *
 * Intent: Shift-copy loop over a fixed cell pair. AR2 = 12160 (rptbd
 * delay slot stm, runs once); BRC is caller-live. Each of the BRC + 1
 * passes (RPTB precedent 5a68/4ebc; RPTBD shape per the vendored TI
 * SPRU172C note in ti-c54x opcode_catalog.def: RSA = PC + 4 = 0x4DA1,
 * REA = 0x4DA4; RPTBD execution stays deferred in the core, flagged):
 * A = *AR2++ unsigned (ldu, 3691 precedent), cell 0x9 = *AR2-- (mvdk,
 * 4ebc precedent), *(AR2++) = low16(A << ASM) (stl a,asm: ASM caller-
 * live 5-bit field -16..+15 assumed, flagged; LDU zeroes the upper
 * bits so long is exact), AR2-- (mar). The pass is AR2-neutral, so the
 * RSA reading does not change the net effect (flagged, verified by
 * inspection). Return. Bound 4D9D-4DA6.
 */
void sub_4D9D(int brc_live, int asm_live)
{
    int *ar2;
    int i;
    ar2 = (int *)12160;                              /* rptbd delay: stm #12160,ar2 */
    for (i = 0; i < brc_live + 1; i++) {              /* rptbd 0x4da4 */
        long a;
        unsigned long shifted;
        a = (unsigned long)(unsigned)*ar2++;         /* ldu *ar2+,a */
        *(volatile int *)0x9 = *ar2--;                /* mvdk *ar2-,0x9 */
        shifted = (unsigned long)(a & 0xFFFF);
        if (asm_live >= 0)
            shifted <<= asm_live;
        else
            shifted >>= -asm_live;
        *ar2++ = (int)(shifted & 0xFFFF);            /* stl a,asm,*ar2+ */
        ar2--;                                       /* mar *ar2- */
    }
    /* ret */
}
