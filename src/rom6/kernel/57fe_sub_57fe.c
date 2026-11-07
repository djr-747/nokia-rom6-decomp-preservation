/* ROM6 0x57FE SUB_57FE -- 13w.
 * Verified encoding: src/rom6/kernel/57fe_sub_57fe.asm (recombine MATCH).
 * ORIGIN 0x57FE
 * EXPECT: F074 059C 7712 0912 7713 091C EC08 E589 F274 425F 7712 091C FC00
 *
 * Intent: Block copy plus call. Runs 0x59C; copies 9 words (rpt #8) from AR2 = 2322 to AR3 = 2332 (mvdd *ar2+,*ar3+); calls 0x425F with AR2 = 2332 in the calld delay slot (executes first), return.
 */
extern void sub_059C(void);
extern void sub_425F(void);

static int *G_AR2;
static int *G_AR3;

void sub_57FE(void)
{
    int i;
    int *src;
    int *dst;
    sub_059C();                                  /* call 0x59c */
    G_AR2 = (int *)2322;                         /* stm #2322,ar2 */
    G_AR3 = (int *)2332;                         /* stm #2332,ar3 */
    src = G_AR2; dst = G_AR3;
    for (i = 0; i < 9; i++)                       /* rpt #8 */
        *dst++ = *src++;                         /* mvdd *ar2+,*ar3+ */
    G_AR2 = (int *)2332;                         /* calld delay slot */
    sub_425F();                                  /* calld 0x425f */
    /* ret */
}
