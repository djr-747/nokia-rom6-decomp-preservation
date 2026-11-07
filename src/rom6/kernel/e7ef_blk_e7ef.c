/* ROM6 0xE7EF BLK_E7EF -- 29w.
 * Verified encoding: src/rom6/kernel/e7ef_blk_e7ef.asm (recombine MATCH).
 * ORIGIN 0xE7EF
 * EXPECT: F074 05B0 F074 9DDD 76F8 347F 0000 76F8 244C 0000 76F8 3480 0000 76F8 3B8C 0000 76F8 3B88 0000 76F8 3B89 0000 F274 2262 7712 000C F074 05B0 FC00
 *
 * Intent: Zero-block plus call pair. Runs 0x5B0 then the 0x9DDD stub (C: stub_9DDD); six zero stores (cells 0x347F/0x244C/0x3480/0x3B8C/0x3B88/0x3B89); calls 0x2262 with AR2 = 12 in the calld delay slot (executes first); runs 0x5B0 again; return.
 */
extern void sub_05B0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void stub_9DDD(void);
extern void sub_2262(void); /* unowned @0x2262; see docs/evidence/extern-triage.md */

static int *G_AR2;

void blk_E7EF(void)
{
    sub_05B0();                                  /* call 0x5b0 */
    stub_9DDD();                                 /* call 0x9ddd */
    *(volatile int *)0x347F = 0;             /* st */
    *(volatile int *)0x244C = 0;             /* st */
    *(volatile int *)0x3480 = 0;             /* st */
    *(volatile int *)0x3B8C = 0;             /* st */
    *(volatile int *)0x3B88 = 0;             /* st */
    *(volatile int *)0x3B89 = 0;             /* st */
    G_AR2 = (int *)12;                          /* calld delay slot */
    sub_2262();                                  /* calld 0x2262 */
    sub_05B0();                                  /* call 0x5b0 */
    /* ret */
}
