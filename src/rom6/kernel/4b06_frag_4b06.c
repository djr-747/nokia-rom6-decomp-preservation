/* ROM6 ORIGIN 0x4B06 (38w): FRAG_4B06 -- shift-pack/XOR-fold pair.
 * Verified encoding: src/rom6/kernel/4b06_frag_4b06.asm (recombine MATCH).
 * EXPECT: F6BB 6BF8 0013 0007 7714 2F00 771A 0003 F072 4B14 44E3 0001 1A93 F47E 8094 F030 01FF 11E3 FFFF F330 F800 F600 80E4 FFFF EC03 E59A 7714 2F00 7182 0013 771A 0007 F072 4B2A 1094 1C83 8093 FC00
 *
 * Intent: INTM = 0 (hardware, no C form); cell 0x13 += 7 (addm).
 * AR4 = 12032; BRC = 3; rptb 0x4B14: RSA = 0x4B10, REA = 0x4B14,
 * block [RSA,REA] inclusive per the oracle sequencer end comparator
 * (repeat_block.c: block ends with the instruction whose last word is
 * REA), 4 passes: A = (AR3[1] << 16) | *AR3++
 * (ld long-offset plus or-with-post-inc), A arith>>= 2 (sfta,
 * grounded), *AR4++ = A-low. Post-pass fixup of the last word:
 * A &= 511; B = *(AR3-1) (long-offset -1 reads the last OR-fed cell);
 * B &= -2048; A += B; *(AR4-1) = A-low (long-offset -1 rewrites the
 * last stored word: low 9 bits of the shifted value plus bit 11+ of
 * the input word). rpt #3: 4x *AR4++ = *AR3++ (mvdd copy).
 * AR4 = 12032 (reset); cell 0x13 = *AR2 (mvdk; AR2 caller-live pointer,
 * read-only). BRC = 7; rptb 0x4B2A: RSA = 0x4B28, REA = 0x4B2A,
 * block inclusive (8 passes): A = *AR4++; A ^= *AR3 (xor Smem, no
 * step, grounded); *AR3++ = A-low. Ret. AR3 advances +16 total in HW
 * (local walk; caller-register live-out flagged); AR4 set in-span;
 * A/B internal; TC untouched. Bound 4B06-4B2B.
 */
extern void port_write_36(int v);                                     /* HW port 36 (per 3273/4b06 spans); no ROM definition */

void frag_4B06(int *ar2_in, int *ar3_in)
{
    long a;
    long b;
    int i;
    int *ar4;
    int *ar3 = ar3_in;

    /* rsbx st1,intm (hardware, no C form) */
    *(volatile int *)0x13 += 7;                  /* addm #7,*(0x13) */
    ar4 = (int *)12032;                         /* stm #12032,ar4 */
    /* stm #3,brc; rptb 0x4b14: [0x4b10,0x4b14], 4 passes */
    for (i = 0; i < 4; i++) {
        a = (long)ar3[1] << 16;                 /* ld *ar3(0x1),16,a */
        a |= (long)(unsigned)*ar3++;            /* or *ar3+,a */
        a >>= 2;                                /* sfta a,-2 (arith) */
        *ar4++ = (int)(a & 0xFFFF);             /* stl a,*ar4+ */
    }
    a &= 511L;                                  /* and #511,a */
    b = (long)*(ar3 - 1);                       /* ld *ar3(0xffff),b */
    b &= -2048L;                                /* and #-2048,b */
    a += b;                                     /* add b,a */
    *(ar4 - 1) = (int)(a & 0xFFFF);             /* stl a,*ar4(0xffff) */
    for (i = 0; i < 4; i++)                     /* rpt #3 */
        *ar4++ = *ar3++;                        /* mvdd *ar3+,*ar4+ */
    ar4 = (int *)12032;                         /* stm #12032,ar4 */
    *(volatile int *)0x13 = *ar2_in;            /* mvdk *ar2,0x13 */
    /* stm #7,brc; rptb 0x4b2a: [0x4b28,0x4b2a] inclusive, 8 passes */
    for (i = 0; i < 8; i++) {
        a = (long)*ar4++;                       /* ld *ar4+,a */
        a ^= (long)*ar3;                        /* xor *ar3,a */
        *ar3++ = (int)(a & 0xFFFF);             /* stl a,*ar3+ */
    }
    /* ret */
}
