/* ROM6 0x446D DISPATCH_TARGET_D -- 7w.
 * Verified encoding: src/rom6/rf/446d_dispatch_target_d.asm (recombine MATCH).
 * ORIGIN 0x446D
 * EXPECT: 4913 1084 F074 4007 7716 0000 FC00
 *
 * Intent: Helper-call plus clear. B = AR3 (live-in), A = *AR4 (live-in), call 0x4007, clear AR6, return the helper result.
 */
extern int sub_4007(int a_in, int b_in);

static int *G_AR6;

int dispatch_target_D_446D(int *par3, int *par4)
{
    int a = sub_4007(*par4, (int)par3);          /* ldm ar3,b; ld *ar4,a; call */
    G_AR6 = (int *)0;                            /* stm #0,ar6 */
    return a;                                    /* ret */
}
