/* ROM6 0x942E COBBA_VERIFY_LOOP -- 37w (span 942E-9452).
 * Verified encoding: src/rom6/rf/942e_cobba_verify_loop.asm (recombine MATCH).
 * ORIGIN 0x942E
 * EXPECT: F074 05BE 7719 00FA 7212 21FB 10F8 20FE FA45 9459 7710 20FF 6180 0400 F830 9459 6180 0100 F830 9453 6180 0200 F830 944B F074 99E6 FC44 F073 942E F274 9A50 7714 009B F846 942E F073 9459
 *
 * Intent: COBBA verify retry loop (branch-reached; no F074 callers,
 * no entry live-ins -- B rides preserved, everything else set
 * before use). Retries dark SUB_05BE (no symbol, opaque) then the
 * AR0-flag tests until MSG_VERIFY_LOOP reports nonzero. Per pass:
 * BK = 250 (stm; unused in-span, caller-observable, not carried).
 * AR2 = MEM[0x21FB] (mvdm; never read in-span, caller-observable,
 * not carried). A = *(0x20FE) (ld). bcd 0x9459,aeq: the 2-word stm
 * (AR0 = 8447) + bitf *AR0,#1024 delay window always runs (520C
 * word-count rule); A == 0 exits to SUB_9459 (forward extern,
 * kernel 9459_sub_9459). Fall: TC = bit10 set (bc 9459,tc exits);
 * TC = bit8 set exits to FRAG_9453 (bc 9453,tc; linked C); TC =
 * bit9 set joins the 944B lane (bc 944b,tc; mid-span in-label).
 * A = MSG_VERIFY_LOOP residue (unbound; 99e6 asm-only, forward
 * extern msg_verify_loop per its symbol); nonzero returns (rc
 * aneq). Else loops to head (b 0x942e). 944B lane: delayed-call
 * into dark SUB_9A50 (calld; forward extern void per the 9453
 * precedent; delay stm #154...#155,ar4 preset dead in C, noted --
 * AR4 = 155 unused in-span, caller-observable, not carried);
 * A = SUB_9A50 residue (unbound); A > 0 loops to head (bc 0x942e,
 * agt, signed per 6871); else tails to SUB_9459 (b 0x9459).
 * A/B outs dark residues (void).
 */
extern void sub_05BE(void);                          /* dark, no symbol */
extern void sub_9459(void);                          /* asm-only, forward extern */
extern void frag_9453(int a_live);                   /* linked C */
extern int msg_verify_loop(void);                    /* asm-only, A-out dark */
extern void routine_9A50(void);                          /* dark (9453 precedent) */

void frag_942E(void)
{
    long a;
    long b;                                          /* preserved, never written */
    long a9a50;                                      /* unbound: SUB_9A50 A residue */
    int *ar0;
    int *ar2;
    int ar4;
    int tc;
    (void)b;
l942e:
    sub_05BE();                                      /* call 0x5be */
    /* stm #250,bk (unused in-span, not carried) */
    ar2 = (int *)(long)*(volatile int *)0x21FB;      /* mvmd (not carried) */
    (void)ar2;
    a = (long)*(volatile int *)0x20FE;               /* ld *(0x20fe),a */
    ar0 = (int *)(long)8447;                         /* bcd delay 1 (always) */
    tc = (*ar0 & 1024) != 0;                         /* bcd delay 2: bitf (always) */
    if (a == 0) {                                    /* bcd 0x9459,aeq taken */
        sub_9459();
        return;
    }
    if (tc) {                                        /* bc 0x9459,tc */
        sub_9459();
        return;
    }
    tc = (*ar0 & 256) != 0;                          /* bitf *ar0,#256 */
    if (tc) {                                        /* bc 0x9453,tc */
        frag_9453((int)a);
        return;
    }
    tc = (*ar0 & 512) != 0;                          /* bitf *ar0,#512 */
    if (tc)                                          /* bc 0x944b,tc */
        goto l944b;
    a = (long)msg_verify_loop();                     /* call 0x99e6 */
    if (a != 0)                                      /* rc aneq */
        return;
    goto l942e;                                      /* b 0x942e */
l944b:
    routine_9A50();                                      /* calld 0x9a50 */
    ar4 = 155;                                       /* calld delay: stm (dead, noted) */
    (void)ar4;
    if (a9a50 > 0)                                   /* bc 0x942e,agt */
        goto l942e;
    sub_9459();                                      /* b 0x9459 */
}
