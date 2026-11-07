/* ROM6 0x5AAC ROUTINE_5AAC -- 28w filter-kernel prologue, tail-calls SEG_5AC8.
 * Verified encoding: src/rom6/kernel/5aac_routine_5aac.asm (recombine MATCH).
 * ORIGIN 0x5AAC
 * EXPECT: F074 059C E724 7711 264C E908 1081 F620 7719 01C8 7710 0000 FF43 F000 0016 62F8 0008 0072 60F8 250F 0022 F820 5AC8 6FF8 352C 0C02 F073 5ACA
 *
 * Intent: Filter-kernel prologue. Runs dark SUB_059C (call). AR4 = entry
 * AR2 (mvmm ar2,ar4; data pointer rides out as par2). A = cell 0x264C - 8
 * (ld *ar1,a with AR1 = 9804 = 0x264C; sub b,a). BK = 456, AR0 = 0
 * (circular scatter base for the SEG_5AC8 rptb loop; hardware state,
 * no C form). A < 0 skips A += 22 (xc 2,alt; XC skips WORDS per op_xc);
 * the shaped A is overwritten by the MPY below (transcribed hand-asm
 * leftover, HYPOTHESIS). A = *(0x8) * 114 (mpy Smem,#lk, signed 16x16
 * into A per op_mpy_smem_lk). TC = (id cell 0x250F == 34) (cmpm; memory
 * ops keep TC per op_cmpm_smem_lk). Mismatch tail-enters FRAG_5AC8
 * (bc 0x5ac8,ntc), which first adds 11036 << 2. Match adds
 * *(0x352C) << 2 (ADD Smem SHIFT: dst = src + (Smem << SHIFT), Smem
 * SXM-sign-extended per op_add_smem_shift; SXM = 1 assumed, flagged) and
 * tail-enters FRAG_5ACA (b 0x5aca = SEG_5AC8+2). Entry via calld F274@4CE4
 * (objdump-verified). Bound 5AAC-5AC7; no RET in span, exits forward.
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_5AC8(long a_live, int *par2);
extern void frag_5ACA(long a_live, int *par2);

void routine_5AAC(int *par2)
{
    long a;
    int tc;

    sub_059C();                                        /* call 0x59c */
    /* mvmm ar2,ar4: AR4 = entry AR2 (par2 rides out) */
    a = (long)*(volatile int *)0x264C - 8L;            /* ld; sub b,a */
    /* stm #456,bk; stm #0,ar0: circular base (hardware, no C form) */
    if (a >= 0)                                        /* xc 2,alt */
        a += 22;                                       /* add #22,a */
    /* shaped A overwritten below (hand-asm leftover, HYPOTHESIS) */
    a = (long)*(volatile int *)0x8 * 114L;             /* mpy */
    tc = (*(volatile int *)0x250F == 34);              /* cmpm */
    if (!tc) {                                         /* bc ntc */
        frag_5AC8(a, par2);
        return;
    }
    /* SXM = 1 sign-extend assumed, flagged */
    frag_5ACA(a + ((long)*(volatile int *)0x352C << 2), par2);  /* b */
}
