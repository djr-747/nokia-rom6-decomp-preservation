/* ROM6 0x9BF8 FRAG_9BF8 -- 27w.
 * Verified encoding: src/rom6/kernel/9bf8_frag_9bf8.asm (recombine MATCH).
 * ORIGIN 0x9BF8
 * EXPECT: 4816 08F8 20FE F845 9C15 6C84 9C07 6F82 0D58 6D94 6D96 F273 9C0C F330 00FF 11D2 6D8C 6D96 F330 00FF F250 00C1 F844 9C13 6D97 F073 9C15
 *
 * Intent: Mask-and-fold with twin tails. A = zero-extended AR6
 * (ldm, oracle leaf zero-extends WORD16 into 40-bit A) minus
 * sign-extended cell 0x20FE (sub Smem, SXM = 1 flagged); zero
 * tail-enters frag_9C15 (dark, extern). banz observes AR4
 * (oracle branch-Sind helper: OBSERVE form takes iff AR4 != 0
 * with NO writeback -- distinct from the postdecrement *-form
 * behind the wave-19 BANZD note): nonzero runs the 9C07 body
 * (B = sign-extended *AR2 with AR2 += AR0, circular +0% wrap
 * needs caller-live BK, linear modeled flagged; B &= 255,
 * upper cleared per the immediate leaf), zero runs the fall
 * body (B = *AR2 arith>>8 per the LD-shift precedent,
 * SXM = 1 flagged; bd to 9C0C whose two delay slots are the
 * 2-word and #255,b, always runs). Both converge: A = B ^ 193
 * (xor-immediate-shift row, SHIFT4 = 0 from the first word,
 * 40-bit logical, exact; B < 256 so long-safe); nonzero
 * tail-enters frag_9C13 (dark, extern); else mar *ar7+ (dead,
 * noted) and tail-branch to frag_9C15. The span never falls
 * through to a return. Bound 9BF8-9C12.
 */
extern void frag_9C15(void); /* joins 9c13_frag_9c13 interior @+0x2; see docs/evidence/extern-triage.md */
extern void frag_9C13(void); /* joins 9c13_frag_9c13; see docs/evidence/extern-triage.md */

void frag_9BF8(int ar6_live, int ar0_live, int *ar2_in, int ar4_live)
{
    int *ar2 = ar2_in;
    long a;
    long b;
    a = (long)(unsigned)ar6_live;                     /* ldm ar6,a (zero-ext) */
    a -= (long)*(volatile int *)0x20FE;              /* sub *(0x20fe),a */
    if (a == 0) {                                    /* bc 0x9c15,aeq */
        frag_9C15();
        return;
    }
    if (ar4_live != 0) {                             /* banz observe (no writeback) */
        b = (long)*ar2;                              /* ld *ar2+%,b */
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
        /* mar *ar4-; mar *ar6+ (dead, noted) */
        b &= 255;                                    /* and #255,b */
    } else {
        b = (long)*ar2 >> 8;                         /* ld *ar2,-8,b (arith) */
        /* mar *ar4+; mar *ar6+ (dead, noted) */
        b &= 255;                                    /* bd delay (always runs) */
    }
    a = b ^ 193;                                     /* xor #193,b,a */
    if (a != 0) {                                    /* bc 0x9c13,aneq */
        frag_9C13();
        return;
    }
    /* mar *ar7+ (dead, noted) */
    frag_9C15();                                      /* b 0x9c15 (tail) */
}
