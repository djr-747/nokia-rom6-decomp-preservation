/* ROM6 0x4986 FRAG_4986 -- 44w cell-gated store pair.
 * Verified encoding: src/rom6/kernel/4986_frag_4986.asm (recombine MATCH).
 * ORIGIN 0x4986
 * EXPECT: 11F8 058C F84F 4996 11F8 2656 F310 000F F84D 4996 6BF8 058C FFFF 68F8 2A87 FDFF 7715 0060 7714 0061 1182 7712 2657 60F8 000B 00F0 F820 49B6 60F8 250F 0022 F820 49B2 81F8 366F 81F8 37B0 60F8 34BF 0003 F830 4ABE F073 4AD8
 *
 * Intent: B = cell 0x58C sign-extended (ld); B <= 0 tail-enters dark 0x4996
 * (bc bleq, forward extern void + return). B = cell 0x2656; B -= 15;
 * B == 0 tail-enters 0x4996 (bc beq). Else cell 0x58C -= 1 (addm);
 * cell 0x2A87 &= -513 (0xFDFF, andm). AR5 = 96, AR4 = 97 (stm, dead
 * post presets, noted); B = *AR2-entry sign-extended (ld, AR2 entry-live);
 * AR2 = 9815 (dead, noted). Cell(DP 0x0B) != 240 runs 0x49B6 (bc ntc; has
 * .asm reading no registers, forward extern void frag_49B6). Cell(DP 8)
 * == 34 stores B-low to cells 0x366F and 0x37B0 (stl pair); != 34 rejoins
 * at 0x49B2 (bc ntc, in-span join). Cell 0x34BF == 3 tail-enters dark 0x4ABE
 * (bc tc, forward extern void); else tail-enters 0x4AD8 (b; has .asm with
 * calad, opaque forward extern void frag_4AD8). B/AR2 entry-live; A
 * untouched. Bound 4986-49B1 (exit F073@49B0->4AD8 + operand 49B1).
 */
extern void frag_4996(void);
extern void frag_49B6(void);
extern void frag_4ABE(void);
extern void frag_4AD8(void);

void frag_4986(int *par2)
{
    long b = (long)*(volatile int *)0x58C;             /* ld *(0x58c),b */

    if (b <= 0) {                                      /* bc 0x4996,bleq */
        frag_4996();
        return;
    }
    b = (long)*(volatile int *)0x2656;                 /* ld *(0x2656),b */
    b -= 15L;                                          /* sub #15,b */
    if (b == 0) {                                      /* bc 0x4996,beq */
        frag_4996();
        return;
    }
    *(volatile int *)0x58C += -1;                      /* addm #-1 */
    *(volatile int *)0x2A87 &= -513;                   /* andm #-513 */
    /* stm #96,ar5; stm #97,ar4 (dead post presets, not modeled) */
    b = (long)*par2;                                   /* ld *ar2,b */
    /* stm #9815,ar2 (dead post preset, not modeled) */
    if (*(volatile int *)0xB != 240) {                 /* cmpm; bc ntc */
        frag_49B6();
        return;
    }
    /* 0x49b2 join */
    if (*(volatile int *)0x8 == 34) {                  /* cmpm; bc ntc */
        *(volatile int *)0x366F = (int)(b & 0xFFFF);   /* stl b */
        *(volatile int *)0x37B0 = (int)(b & 0xFFFF);   /* stl b */
    }
    if (*(volatile int *)0x34BF == 3) {                 /* cmpm; bc tc */
        frag_4ABE();
        return;
    }
    frag_4AD8();                                       /* b 0x4ad8 tail */
}
