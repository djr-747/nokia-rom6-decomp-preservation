/* ROM6 0x5355 DISPATCH_SLED_A -- 13w.
 * Verified encoding: src/rom6/rf/5355_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x5355
 * EXPECT: 1182 F074 580B F820 5362 11F8 250F F074 580B F920 84CF F073 5371
 *
 * Intent: Branch-entered dispatch sled fragment (5282-family; entries
 * via F820/F84D-class branches, no F074 callers). B = *AR2-entry
 * (ld *ar2,b; AR2 live at entry, explicit param). Runs SIEVE_580B
 * (C: sieve_580B); TC threads through the call per the 3691
 * convention (flagged). NTC exits to FRAG_5362 (bc 0x5362,ntc;
 * asm-only, forward extern). Else B = *(0x250F), second sieve pass,
 * NTC conditional-calls SUB_84CF (cc 0x84cf,ntc; C: sub_84CF_init),
 * then jumps into the middle of the 5362 span (b 0x5371; mid-span
 * entry, forward extern frag_5371).
 */
extern void sieve_580B(int b_live);                  /* C: 580b_sieve_580b */
extern void sub_84CF_init(void);                     /* C: 84cf_sub_84cf */
extern void frag_5362(void);                         /* asm-only, forward extern */
extern void frag_5371(void);                         /* mid-span entry into the 5362 span */

void frag_5355(int *ar2)
{
    long b = (long)*ar2;                             /* ld *ar2,b */
    int tc;                                          /* unbound: set by sieve_580B (TC out) */
    sieve_580B((int)b);                              /* call 0x580b */
    /* TC threads through the call (3691 convention, flagged) */
    if (!tc) {                                       /* bc 0x5362,ntc */
        frag_5362();
        return;
    }
    b = (long)*(volatile int *)0x250F;               /* ld *(0x250f),b */
    sieve_580B((int)b);                              /* call 0x580b */
    if (!tc)                                         /* cc 0x84cf,ntc */
        sub_84CF_init();
    frag_5371();                                     /* b 0x5371 */
}
