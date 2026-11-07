/* ROM6 0xC851 STATE_WORKER -- 12w.
 * Verified encoding: src/rom6/kernel/c851_state_worker.asm (recombine MATCH).
 * ORIGIN 0xC851
 * EXPECT: F074 05EA 68F8 051C F3FF 68F8 20F4 F900 69F8 20F4 0002 E900
 *
 * Intent: Flag-cell preset head. Runs dark SUB_05EA (near call); clears
 * bits 12-13 of cell 0x51C (andm #-3073) and bits 8-10 of cell 0x20F4
 * (andm #-1792); sets bit 1 of cell 0x20F4 (orm #2); B = 0. Cells are
 * absolute (16-bit address extension, 3115 precedent); ANDM/ORM fold to
 * C compound assignment per the 3115/33bc precedents. B = 0 runs live
 * into 0xC85D (no C binding yet); fall-through, no return modeled.
 * Bound C851-C85C.
 */
extern void sub_05EA(void);

void state_worker_C851(void)
{
    int b;
    sub_05EA();                                      /* call 0x5ea (near) */
    *(volatile int *)0x51C &= -3073;                /* andm #-3073,*(0x51c) */
    *(volatile int *)0x20F4 &= -1792;               /* andm #-1792,*(0x20f4) */
    *(volatile int *)0x20F4 |= 2;                   /* orm #2,*(0x20f4) */
    b = 0;                                           /* ld #0,b */
    (void)b;                                         /* B live into 0xC85D; fall-through */
}
