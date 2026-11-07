/* ROM6 0x8555 FANOUT_8555 -- 10w.
 * Verified encoding: src/rom6/kernel/8555_fanout_8555.asm (recombine MATCH).
 * ORIGIN 0x8555
 * EXPECT: 4A14 E754 F074 8588 F074 85FD 8A14 F074 853B FC00
 *
 * Intent: fanout orchestrator. Save AR4, point it at AR5, run the
 * block-copy 0x8588 and sub 0x85FD under that aliasing, restore
 * AR4, then run the 0x853B fanout driver and return.
 */
extern void block_copy_8588(int *src);
extern void sub_85FD(void); /* joins 85fd_block_copy_85fd; see docs/evidence/extern-triage.md */
extern void fanout26_853B(int **pp1, int *ar4, int *ar6);

void fanout_8555(int **pp5, int **pp1, int *ar6)
{
    int *saved_ar4 = *pp1;                    /* pshm ar4 (conceptual) */
    int *ar4 = *pp5;                          /* mvmm ar5,ar4 */
    block_copy_8588(ar4);                     /* call 0x8588 */
    sub_85FD();                               /* call 0x85fd */
    ar4 = saved_ar4;                          /* popm ar4 */
    fanout26_853B(pp1, ar4, ar6);             /* call 0x853b */
    /* ret */
}
