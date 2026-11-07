/* ROM6 0xB41C FRAG_B41C -- 21w.
 * Verified encoding: src/rom6/kernel/b41c_frag_b41c.asm (recombine MATCH).
 * ORIGIN 0xB41C
 * EXPECT: 7715 B550 7716 B565 F020 B55C F074 AEEC F074 AF40 F074 A582 7713 B550 7716 B565 F020 B55C F074 AF16 FC00
 *
 * Intent: Preset call sandwich. AR5 = -19120, AR6 = -19099, A = -19108 feed 0xAEEC, 0xAF40, 0xA582; AR3 = -19120, AR6 = -19099, A = -19108 feed 0xAF16; return.
 */
extern void sub_AEEC(void); /* joins aeec_regfield_helper; see docs/evidence/extern-triage.md */
extern void sub_AF40(void); /* joins af40_routine_af40; see docs/evidence/extern-triage.md */
extern void sub_A582(void); /* joins a582_routine_a582; see docs/evidence/extern-triage.md */
extern void sub_AF16(void); /* joins af16_routine_af16; see docs/evidence/extern-triage.md */

static int *G_AR5;
static int *G_AR6;
static int *G_AR3;

void frag_B41C(void)
{
    int a = -19108;                              /* ld #-19108,a */
    G_AR5 = (int *)-19120;                       /* stm #-19120,ar5 */
    G_AR6 = (int *)-19099;                       /* stm #-19099,ar6 */
    (void)a;
    sub_AEEC();                                  /* call 0xaeec */
    sub_AF40();                                  /* call 0xaf40 */
    sub_A582();                                  /* call 0xa582 */
    a = -19108;                                  /* ld #-19108,a */
    G_AR3 = (int *)-19120;                       /* stm #-19120,ar3 */
    G_AR6 = (int *)-19099;                       /* stm #-19099,ar6 */
    (void)a;
    sub_AF16();                                  /* call 0xaf16 */
    /* ret */
}
