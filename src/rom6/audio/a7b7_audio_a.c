/* ROM6 0xA7B7 AUDIO_A -- 52w.
 * Verified encoding: src/rom6/audio/a7b7_audio_a.asm (recombine MATCH).
 * ORIGIN 0xA7B7
 * EXPECT: F074 0660 F074 3EE1 60F8 250F 0022 F820 A7DD 11F8 0542 F310 0003 F84F A7C9 F010 1016 FC42 10F8 34BF F844 A7D2 76F8 0543 0006 F073 A7E8 F010 0003 F846 A7D8 F073 A7E5 76F8 0543 0008 F073 A7E8 6FF8 0542 0D5E FA4F A7E5 F010 0EB8 FC42 76F8 0543 0007 F074 3986 FC00
 *
 * Intent: Audio path A with in-span joins. Runs dark 0x660 (A rides
 * through, void) then PORT13_STABLE_READ 0x3EE1 (A-OUT proven by the
 * 3EE3 loop shape -- entry A is overwritten with the stable reading;
 * the old preserve-A reading was wrong, fixed this wave). Cell
 * 0x250F != 34 joins the tail block at A7DD (bc ntc; in-span: A7DD
 * is offset 38, the ld-shift block, not a separate span). B = cell
 * 0x542 - 3, <= 0 joins at A7C9 (bc bleq; in-span offset 18, the
 * ld-34bf cell read). A -= 4118, >= 0 returns (rc ageq). A7C9: A =
 * cell 0x34BF, nonzero joins at A7D2 (bc aneq; in-span offset 27,
 * the sub-3 cell test). Else cell 0x543 = 6, joins the call site at
 * A7E8 (b; in-span offset 49, the dispatch call). A7D2: A -= 3, > 0
 * joins at A7D8 (bc agt; in-span offset 33, the st-8 cell write).
 * Else joins at A7E5 (b; in-span offset 46, the st-7 cell write,
 * shared with the bcd tail below). A7D8/A7E5: cell 0x543 = 8 or 7,
 * join the call site. A7DD: B = cell 0x542 >> 2 (ld -2 shift;
 * SXM-on-entry unknown, plain right shift per small-count use,
 * noted); bcd delay slots always run (A -= 3768; A >= 0 returns via
 * rc ageq); taken and not-taken both reach the st-7 cell write (bc
 * bleq target A7E5 equals the fall-through word, convergence
 * noted, modeled straight). Call site A7E8: runs
 * CMD_DISPATCH_PORT15 0x3986 (forward extern), return. All six
 * branch targets resolved in-span by absolute offset; no dark
 * forward externs needed. SUB per op_sub. Bound per .asm header
 * 52w (recombine MATCH).
 */
extern void sub_0660(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int port13_stable_read(void);
extern void sub_3986(void);

void audio_A_A7B7(int a_live)
{
    int a = a_live;                  /* entry A (3EE1 overwrites) */
    int b;
    sub_0660();                                  /* call 0x660 */
    a = port13_stable_read();            /* call 0x3ee1 (A-out) */
    if (*(volatile int *)0x250F != 34)           /* cmpm, bc ntc */
        goto L_A7DD;                             /* in-span join */
    b = *(volatile int *)0x542 - 3;          /* ld; sub #3,b */
    if (b <= 0)                                  /* bc 0xa7c9,bleq */
        goto L_A7C9;                             /* in-span join */
    a -= 4118;                                   /* sub #4118,a */
    if (a >= 0)                                  /* rc ageq */
        return;
L_A7C9:
    a = *(volatile int *)0x34BF;             /* ld *(0x34bf),a */
    if (a != 0)                                  /* bc 0xa7d2,aneq */
        goto L_A7D2;                             /* in-span join */
    *(volatile int *)0x543 = 6;              /* st #6,*(0x543) */
    goto L_A7E8;                                 /* b 0xa7e8 (call site) */
L_A7D2:
    a -= 3;                                      /* sub #3,a */
    if (a > 0)                                   /* bc 0xa7d8,agt */
        goto L_A7D8;                             /* in-span join */
    goto L_A7E5;                                 /* b 0xa7e5 */
L_A7D8:
    *(volatile int *)0x543 = 8;              /* st #8,*(0x543) */
    goto L_A7E8;                                 /* b 0xa7e8 (call site) */
L_A7DD:
    b = *(volatile int *)0x542 >> 2;         /* ld *(0x542),-2,b */
    /* bcd delay slots (always run): */
    a -= 3768;                                   /* sub #3768,a */
    if (a >= 0)                                  /* rc ageq */
        return;
    /* bc 0xa7e5,bleq target == fall-through word (convergent) */
L_A7E5:
    *(volatile int *)0x543 = 7;              /* st #7,*(0x543) */
L_A7E8:
    sub_3986();                       /* call 0x3986 */
    /* ret */
}
