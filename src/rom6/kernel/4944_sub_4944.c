/* ROM6 0x4944 SUB_4944 -- 66w twin-gate store with mode select.
 * Verified encoding: src/rom6/kernel/4944_sub_4944.asm (recombine MATCH).
 * ORIGIN 0x4944
 * EXPECT: F074 059E 11F8 262B F310 00B0 F84C 4996 60F8 250F 0022 F820 4986 60F8 34BF 0001 F830 4974 60F8 34BF 0004 F830 4974 60F8 34BF 0003 11F8 3670 F84F 4972 11F8 366F F310 000F F84D 4972 6BF8 3670 FFFF 7715 2A87 FF30 7715 0495 6885 FDFF F820 4996 11F8 37B1 F84F 4996 11F8 37B0 F310 000F F84D 4996 6BF8 37B1 FFFF 68F8 2A87 FDFF F073 4996
 *
 * Intent: Runs dark SUB_059E (call, forward extern void). B = cell 0x262B
 * - 176; nonzero tail-enters FRAG_4996 (bc bneq; C-bound void). Cell(DP 8)
 * != 34 tail-enters FRAG_4986 with entry AR2 (bc ntc; C-bound
 * frag_4986(par2), passthrough param). Cell 0x34BF == 1 or == 4 (cmpm
 * pair, TC-only) rejoins at 0x4974 (bc tc; in-span join, not a tail).
 * Else TC3 = (cell 0x34BF == 3) (cmpm; TC survives the ld/sub/bc/addm/
 * stm/xc below: LD/SUB/ADD preserve TC per op_ld_k/op_sub_lk/op_add_lk,
 * memory ops mutate no status per the memory-effect contract, XC executes
 * at most a flag-free stm). B = cell 0x3670; B <= 0 rejoins 0x4972 (bc
 * bleq). B = cell 0x366F - 15; B == 0 rejoins 0x4972 (bc beq). Else cell
 * 0x3670 -= 1 (addm); AR5 = TC3 ? 1173 : 10887 (xc 2,tc over the stm);
 * *AR5 &= -513 (andm). At 0x4972 (in-span): TC3 clear tail-enters FRAG_4996
 * (bc ntc). Else falls into 0x4974: B = cell 0x37B1; B <= 0 tail-enters
 * 0x4996 (bc bleq); B = cell 0x37B0 - 15; B == 0 tail-enters 0x4996 (bc
 * beq); cell 0x37B1 -= 1; cell 0x2A87 &= -513; tail-enters 0x4996 (b).
 * 0x4974 is the in-span ld, 0x4972 the in-span bc -- no externs for either.
 * A untouched; B/AR5 internal; AR2 entry passthrough. Bound 4944-4985
 * (exit F073@4984->4996 + operand 4985).
 */
extern void sub_059E(void);
extern void frag_4996(void);
extern void frag_4986(int *par2);

void frag_4944(int *par2)
{
    long b;

    sub_059E();                                        /* call 0x59e */
    b = (long)*(volatile int *)0x262B - 176L;          /* ld/sub */
    if (b != 0) {                                      /* bc 0x4996,bneq */
        frag_4996();
        return;
    }
    if (*(volatile int *)0x8 != 34) {                  /* cmpm; bc ntc */
        frag_4986(par2);                               /* AR2 passthrough */
        return;
    }
    if (*(volatile int *)0x34BF != 1 &&                 /* cmpm pair */
        *(volatile int *)0x34BF != 4) {                /* bc 0x4974,tc */
        int tc3 = (*(volatile int *)0x34BF == 3);      /* cmpm (TC3) */
        b = (long)*(volatile int *)0x3670;             /* ld *(0x3670),b */
        if (b > 0) {                                   /* bc 0x4972,bleq */
            b = (long)*(volatile int *)0x366F - 15L;    /* ld/sub */
            if (b != 0) {                              /* bc 0x4972,beq */
                *(volatile int *)0x3670 += -1;         /* addm #-1 */
                {
                    int *par5 = (int *)(tc3 ? 1173 : 10887); /* xc 2,tc */
                    *par5 &= -513;                     /* andm #-513 */
                }
            }
        }
        /* 0x4972 join: TC3 (cmpm result) still live */
        if (!tc3) {                                    /* bc 0x4996,ntc */
            frag_4996();
            return;
        }
    }
    /* 0x4974 join */
    b = (long)*(volatile int *)0x37B1;                 /* ld *(0x37b1),b */
    if (b <= 0) {                                      /* bc 0x4996,bleq */
        frag_4996();
        return;
    }
    b = (long)*(volatile int *)0x37B0 - 15L;           /* ld/sub */
    if (b == 0) {                                      /* bc 0x4996,beq */
        frag_4996();
        return;
    }
    *(volatile int *)0x37B1 += -1;                     /* addm #-1 */
    *(volatile int *)0x2A87 &= -513;                   /* andm #-513 */
    frag_4996();                                       /* b 0x4996 tail */
}
