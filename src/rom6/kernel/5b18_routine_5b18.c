/* ROM6 0x5B18 ROUTINE_5B18 -- 14w nibble unpacker, one EXPECT.
 * Verified encoding: src/rom6/kernel/5b18_routine_5b18.asm (recombine MATCH).
 * ORIGIN 0x5B18
 * EXPECT: F074 05FC 771A 0003 1093 F072 5B22 F130 000F 8192 F45C 6C89 5B1A FC00
 *
 * Intent: Little-endian nibble unpack. Runs dark SUB_05FC (call). BRC = 3
 * re-arms a 4-iteration RPTB over: B = A & 15 (and #15,a,b: A kept;
 * immediate zero-extended per op_logical_immediate); *(AR2) = B-low,
 * AR2++ (stl); A >>= 4 (ld a,-4,a: LD src,SHFT per op_ld_src_shift,
 * SXM-arithmetic assumed, flagged). Four nibbles per word, LE-first.
 * Outer BANZ over AR1 (test-then-decrement per op_branch_sind_common:
 * taken = (AR1 != 0); AR1 live-in from the caller, count = caller AR1):
 * AR1 = 1 gives one outer pass (the 4 calld entries 4BE0/4C4C/4CDD/4CF9
 * set their own counts, trace-confirmable). Entry AR3 = source word
 * (*AR3++ per pass), entry AR2 = nibble sink. A-live-out (word >> 16,
 * small) unused by the span; B/T dead at RET @5B25. Bound 5B18-5B25.
 */
extern void sub_05FC(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void routine_5B18(int *par2, int *par3, int ar1_live)
{
    long a;
    long b;
    int ar1 = ar1_live;
    int take;
    int k;

    sub_05FC();                                        /* call 0x5fc */
    /* stm #3,brc re-armed below as the 4-count */
    do {                                         /* banz *ar1- outer */
        a = (long)*par3++;                       /* ld *ar3+,a */
        for (k = 0; k < 4; k++) {                /* rptb 0x5b22 */
            b = a & 15L;                         /* and #15,a,b */
            *par2++ = (int)(b & 0xFFFF);         /* stl b,*ar2+ */
            a >>= 4;                             /* ld a,-4,a (SXM?) */
        }
        take = (ar1 != 0);                       /* banz test-then-dec */
        ar1 = (ar1 - 1) & 0xFFFF;
    } while (take);                              /* banz 0x5b1a */
    /* ret @5B25 */
}
