/* ROM6 0x54BD MSG_STAGE_54BD -- 59w.
 * Verified encoding: src/rom6/kernel/54bd_msg_stage_54bd.asm (recombine MATCH).
 * ORIGIN 0x54BD
 * EXPECT: 76F8 2EFD 0000 10F8 2547 F030 00F0 F010 00B0 F844 54CB 68F8 0537 FC97 7712 2547 1082 F030 00F0 F010 00D0 F844 54DB 68F8 0537 FCF7 F274 2262 7712 0006 60F8 2546 0022 F820 54E6 76F8 3490 0000 70F8 34BF 34C0 7712 2541 7713 250A EC07 E589 7712 2549 7713 2512 61F8 054F 0010 F820 54F8 E501 F073 5503
 *
 * Intent: Message-producer stage with masked selects and a calld lane. Cell 0x2EFD cleared (st);
 * A = (cell 0x2547 & 240) - 176 (ld/and/sub); nonzero joins the 54CB lane (bc aneq); else cell 0x537
 * &= -873 (andm). Lane: AR2 = 9543; A = (cell AR2 & 240) - 208; nonzero joins 54DB (bc aneq); else cell
 * 0x537 &= -777; AR2 = 6 (calld delay, runs first); delayed call into dark SUB_2262 (forward extern void,
 * 84CF). TC = (cell 0x2546 == 34, cmpm); clear joins 54E6 (bc ntc); else cell 0x3490 cleared and cell 0x34BF
 * = cell 0x34C0 (st + mvkd seed). AR2 = 9537; AR3 = 9482; 8x linear mvdd copy (rpt #7). AR2 = 9545;
 * AR3 = 9490; TC = cell 0x54F bit 4 (bitf); clear tail-joins frag_54F8 (bc ntc; C-bound, AR2/AR3 passed);
 * else single mvdd *AR2 -> *AR3 and tail-join frag_5503 (b; C-bound). No caller-live regs (all set in-span).
 */
extern void sub_2262(void); /* unowned @0x2262; see docs/evidence/extern-triage.md */
extern void frag_54F8(int *par2, int *par3);
extern void frag_5503(void);

void frag_54BD(void)
{
    long a;
    int *ar2;
    int *ar3;
    int i;


    *(volatile int *)0x2EFD = 0;                           /* st #0,*(0x2efd) */
    a = (long)*(volatile int *)0x2547 & 240L;              /* ld; and #240,a */
    a = a - 176;                                           /* sub #176,a */
    if (a != 0)                                            /* bc 0x54cb,aneq */
        goto l54cb;
    *(volatile int *)0x537 &= -873;                        /* andm #-873 */
l54cb:
    ar2 = (int *)9543;                                     /* stm #9543,ar2 */
    a = (long)*ar2 & 240L;                                 /* ld; and #240,a */
    a = a - 208;                                           /* sub #208,a */
    if (a != 0)                                            /* bc 0x54db,aneq */
        goto l54db;
    *(volatile int *)0x537 &= -777;                        /* andm #-777 */
    ar2 = (int *)6;                                        /* calld delay: stm (runs first) */
    sub_2262();                                            /* calld 0x2262 (dark) */
l54db:
    if (*(volatile int *)0x2546 != 34)                     /* cmpm; bc 0x54e6,ntc */
        goto l54e6;
    *(volatile int *)0x3490 = 0;                           /* st #0,*(0x3490) */
    *(volatile int *)0x34BF = *(volatile int *)0x34C0;    /* mvkd seed */
l54e6:
    ar2 = (int *)9537;                                     /* stm #9537,ar2 */
    ar3 = (int *)9482;                                     /* stm #9482,ar3 */
    for (i = 0; i < 8; i++)                                /* rpt #7 */
        *ar3++ = *ar2++;                                   /* mvdd *ar2+,*ar3+ */
    ar2 = (int *)9545;                                     /* stm #9545,ar2 */
    ar3 = (int *)9490;                                     /* stm #9490,ar3 */
    if ((*(volatile int *)0x54F & 16) == 0) {               /* bitf; bc 0x54f8,ntc */
        frag_54F8(ar2, ar3);
        return;
    }
    *ar3 = *ar2;                                           /* mvdd *ar2,*ar3 */
    frag_5503();                                           /* b 0x5503 (tail) */
}
