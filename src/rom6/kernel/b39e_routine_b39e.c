/* ROM6 0xB39E ROUTINE_B39E -- 18w.
 * Verified encoding: src/rom6/kernel/b39e_routine_b39e.asm (recombine MATCH).
 * ORIGIN 0xB39E
 * EXPECT: 7715 B52F 7716 B541 F020 B53F F074 AEEC F074 A4BA 7713 B52F 7716 B541 F020 B53F F074 AF16 FC00
 *
 * Intent: Preset call sandwich. AR5 = -19153, AR6 = -19135, A = -19137 feed 0xAEEC then 0xA4BA; AR3 = -19153, AR6 = -19135, A = -19137 feed 0xAF16, return.
 */
extern void sub_AEEC(void); /* joins aeec_regfield_helper; see docs/evidence/extern-triage.md */
extern void routine_A4BA(void);
extern void sub_AF16(void); /* joins af16_routine_af16; see docs/evidence/extern-triage.md */

static int *G_AR5;
static int *G_AR6;
static int *G_AR3;

void routine_B39E(void)
{
    int a = -19137;                              /* ld #-19137,a */
    G_AR5 = (int *)-19153;                       /* stm #-19153,ar5 */
    G_AR6 = (int *)-19135;                       /* stm #-19135,ar6 */
    (void)a;
    sub_AEEC();                                  /* call 0xaeec */
    routine_A4BA();                                  /* call 0xa4ba */
    a = -19137;                                  /* ld #-19137,a */
    G_AR3 = (int *)-19153;                       /* stm #-19153,ar3 */
    G_AR6 = (int *)-19135;                       /* stm #-19135,ar6 */
    (void)a;
    sub_AF16();                                  /* call 0xaf16 */
    /* ret */
}
