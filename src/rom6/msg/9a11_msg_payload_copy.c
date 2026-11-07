/* ROM6 0x9A11 MSG_PAYLOAD_COPY -- 38w.
 * Verified encoding: src/rom6/msg/9a11_msg_payload_copy.asm (recombine MATCH).
 * ORIGIN 0x9A11
 * EXPECT: F074 05D0 FC4F F021 00FA 08F8 2200 F620 FC47 F67F 61F8 20FF 1000 F830 9A37 FA08 9A2F 7710 0001 47F8 0008 E58D 6DC3 F7BB 69F8 20FF 1000 F6EB 7313 21FC F000 FFFF 47F8 0008 E58D FE00 7313 21FC
 *
 * Intent: Message payload block copier (called from 0x9429). Runs
 * dark SUB_05D0 (no symbol, opaque; A/B outs dark residues, carried
 * as unbound locals). B <= 0 returns (rc bleq, op_rc taken-return).
 * A = 500 - *(0x2200) - B (ld #250,1,a: 250<<1; sub Smem; sub
 * B,A); A <= 0 returns (rc aleq). A = B >> 1 arith, C = B-bit0
 * (sfta b,-1,a; SFTA carry ground truth). TC = (*(0x20FF) & 4096)
 * != 0 (bitf, 5d38 polarity); set tail-enters FRAG_9A37 (bc
 * 0x9a37,tc; asm-only, forward extern). bcd 0x9a2f,nc on the sfta
 * carry (bitf/bc preserve C): the 2-word stm #1,ar0 delay fills the
 * window and always runs (520C word-count rule); AR0 = 1 is dead
 * in-span (caller-observable, not carried). C-clear (B even) path:
 * A -= 1 (add #-1,a at 9A2F), counted copy, retd. C-set (B odd)
 * path: counted copy (*AR2++ to *AR3+0% circular, BK wrap flagged),
 * AR3 circular -1 (mar *ar3-%, BK flagged), INTM = 1 (ssbx,
 * hardware, no C form), done flag MEM[0x20FF] |= 4096 (orm), reted.
 * Both returns save AR3 to MEM[0x21FC] in their delay word (mvmd;
 * reted/retd 2-word windows filled by the mvmd, always runs).
 * AR2/AR3 entry-live advancing: int** writebacks (2e64 precedent).
 * RPT count = MEM[0x8] + 1 per pass (rpt Smem; dark count, volatile
 * read). A/B outs dark 05D0 residues (void, flagged).
 */
extern void sub_05D0(void);                          /* dark, no symbol */
extern void frag_9A37(void);                         /* asm-only, forward extern */

void frag_9A11(int **ppar2, int **ppar3)
{
    long a;
    long b;                                          /* unbound: SUB_05D0 B residue */
    int c;
    int *ar2 = *ppar2;
    int *ar3 = *ppar3;
    int ar0;
    int n;
    int i;
    sub_05D0();                                      /* call 0x5d0 */
    if (b <= 0) {                                    /* rc bleq */
        *ppar2 = ar2;
        *ppar3 = ar3;
        return;
    }
    a = 500L - (long)*(volatile int *)0x2200 - b;    /* ld #250,1,a; sub; sub b,a */
    if (a <= 0) {                                    /* rc aleq */
        *ppar2 = ar2;
        *ppar3 = ar3;
        return;
    }
    c = (int)(b & 1L);                               /* sfta carry-out (B-bit0) */
    a = b >> 1;                                      /* sfta b,-1,a (arith) */
    if ((*(volatile int *)0x20FF & 4096) != 0) {     /* bitf; bc 0x9a37,tc */
        *ppar2 = ar2;
        *ppar3 = ar3;
        frag_9A37();
        return;
    }
    ar0 = 1;                                         /* bcd delay: stm (always runs) */
    (void)ar0;                                       /* AR0 dead in-span, not carried */
    if (c == 0) {                                    /* bcd 0x9a2f,nc taken */
        a += -1;                                     /* add #-1,a */
        n = *(volatile int *)0x8;                    /* rpt *(0x8) */
        for (i = 0; i <= n; i++)                     /* RPT Smem runs Smem+1 */
            *ar3 = *ar2++;                           /* mvdd *ar2+,*ar3+0% (BK flagged) */
        *(volatile int *)0x21FC = (int)(long)ar3;    /* mvmd ar3,0x21fc (delay) */
        *ppar2 = ar2;
        *ppar3 = ar3;
        return;                                      /* retd (delay above) */
    }
    n = *(volatile int *)0x8;                        /* rpt *(0x8) */
    for (i = 0; i <= n; i++)
        *ar3 = *ar2++;                               /* mvdd *ar2+,*ar3+0% (BK flagged) */
    ar3--;                                           /* mar *ar3-% (BK flagged) */
    /* ssbx st1,intm (hardware, no C form) */
    *(volatile int *)0x20FF |= 4096;                 /* orm #4096,*(0x20ff) */
    *(volatile int *)0x21FC = (int)(long)ar3;        /* mvmd ar3,0x21fc (delay) */
    *ppar2 = ar2;
    *ppar3 = ar3;
    /* reted (delay above) */
}
