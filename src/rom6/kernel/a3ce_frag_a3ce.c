/* ROM6 0xA3CE FRAG_A3CE -- 7w.
 * Verified encoding: src/rom6/kernel/a3ce_frag_a3ce.asm (recombine MATCH).
 * ORIGIN 0xA3CE
 * EXPECT: F074 A3D5 FB44 39F0 7712 04D3 FC00
 *
 * Intent: OR-measure plus conditional call. Runs ROUTINE_A3D5; the AR2 = 1235 preset executes in the ccd delay slot (always), then calls 0x39F0 only when the measure is nonzero (ccd aneq), return.
 */
extern int routine_A3D5(void);
extern void sub_39F0(void);

static int *G_AR2;

void frag_A3CE(void)
{
    int a = routine_A3D5();                      /* call 0xa3d5 */
    G_AR2 = (int *)1235;                         /* ccd delay slot: always */
    if (a != 0)                                  /* ccd 0x39f0,aneq */
        sub_39F0();
    /* ret */
}
