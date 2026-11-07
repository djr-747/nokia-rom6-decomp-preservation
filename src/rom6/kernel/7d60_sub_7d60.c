/* ROM6 0x7D60 SUB_7D60 -- 20w.
 * Verified encoding: src/rom6/kernel/7d60_sub_7d60.asm (recombine MATCH).
 * ORIGIN 0x7D60
 * EXPECT: 10F8 0914 08F8 2EF8 7717 264F 7687 0002 F110 0008 FD45 8087 F010 0011 FD4D 8187 FD45 8087 1087 FC00
 *
 * Intent: Chained conditional stores. A = cell 0x914 minus cell 0x2EF8; cell 0x9807 = 2; B = A - 8 (sub, dst = src minus operand per ti-c54x op_sub); A == 0 stores A (xc 1,aeq, exact); A -= 17; B == 0 stores B (xc 1,beq, exact, stores 0); A == 0 stores A (xc 1,aeq, exact, stores 0); returns cell 0x9807 (2 unless any gate fired, then 0). Bound 7D60-7D73, first exit at 7D73.
 */
int sub_7D60(void)
{
    int a = *(volatile int *)0x914 -
              *(volatile int *)0x2EF8;         /* ld, sub */
    int b;
    *(volatile int *)0x9807 = 2;             /* stm #9807,ar7; st */
    b = a - 8;                                   /* sub #8,a,b */
    if (a == 0)                                  /* xc 1,aeq */
        *(volatile int *)0x9807 = a;         /* stl a,*ar7 */
    a -= 17;                                     /* sub #17,a */
    if (b == 0)                                  /* xc 1,beq */
        *(volatile int *)0x9807 = b;         /* stl b,*ar7 */
    if (a == 0)                                  /* xc 1,aeq */
        *(volatile int *)0x9807 = a;         /* stl a,*ar7 */
    return *(volatile int *)0x9807;          /* ld *ar7,a; ret */
}
