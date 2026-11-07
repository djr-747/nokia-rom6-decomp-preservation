/* ROM6 0x8813 ROUTINE_8813 -- 14w.
 * Verified encoding: src/rom6/kernel/8813_routine_8813.asm (recombine MATCH).
 * ORIGIN 0x8813
 * EXPECT: F074 0590 E800 80F8 0551 80F8 0550 EC1F 7308 11BA EC0F 7308 11DA FC00
 *
 * Intent: Table zero-fill. Runs 0x590; A = 0 into cells 0x551/0x550; 32 stores (rpt #31) of AL to 0x11BA (mvmd al); 16 stores (rpt #15) of AL to 0x11DA; return.
 */
extern void sub_0590(void);

void routine_8813(void)
{
    int i;
    sub_0590();                                  /* call 0x590 */
    *(volatile int *)0x551 = 0;              /* ld #0,a; stl */
    *(volatile int *)0x550 = 0;              /* stl */
    for (i = 0; i < 32; i++)                     /* rpt #31 */
        *(volatile int *)0x11BA = 0;         /* mvmd al,0x11ba */
    for (i = 0; i < 16; i++)                     /* rpt #15 */
        *(volatile int *)0x11DA = 0;         /* mvmd al,0x11da */
    /* ret */
}
