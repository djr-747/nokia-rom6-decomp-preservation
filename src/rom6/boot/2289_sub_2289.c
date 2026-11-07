/* ROM6 0x2289 SUB_2289 -- 81w.
 * Verified encoding: src/rom6/boot/2289_sub_2289.asm (recombine MATCH).
 * ORIGIN 0x2289
 * EXPECT: F074 059C 12F8 087B 08F8 087E F010 0800 E900 F845 22B4 12F8 087E F000 0800 8812 13F8 087D F84D 22B4 12F8 087F F520 F84A 22A5 12F8 087D E900 F010 0001 881A 12F8 087B 8813 F072 22AE 1292 8093 4813 730B 087D 7308 087B 10F8 0872 F050 0004 F074 22CF F845 22BD FC00 7712 0536 3292 E801 F482 1A82 8082 60F8 0536 0006 FC20 F074 059C F274 2262 7712 0005 FC00 7711 0872 7681 0000 69F8 0029 0008 68F8 0029 FFF7 FC00
 *
 * Intent: Sample-lane select with rptb fill and masked tail. Runs RAM-resident SUB_059C (forward extern);
 * A = cell 0x87B unsigned - cell 0x87E unsigned - 2048 (ldu/sub/sub); B = 0; A == 0 joins the 22B4 lane
 * (bc aeq). Else A = cell 0x87E unsigned + 2048 (ldu/add); AR2 = A-low (stlm); B = cell 0x87D unsigned;
 * B == 0 joins 22B4 (bc beq). A = cell 0x87F unsigned - B (ldu/sub); A >= 0 joins 22A5 (bc bgeq); else
 * A = cell 0x87D unsigned, B = 0. A -= 1 (sub); BRC = A-low; A = cell 0x87B unsigned (ldu); AR3 = A-low;
 * (BRC+1)x rptb copy *AR2++ to *AR3++ (ldu/stl). A = AR3 register value (ldm); cell 0x87D = B-low,
 * cell 0x87B = A-low (mvmd pair). 22B4 lane: A = cell 0x872; A ^= 4 (xor); runs frag_22CF (interior call,
 * same file); A == 0 joins the 22BD lane (bc aeq), else return. Lane: AR2 = 1334; ASM = *AR2++ then ASM = 1
 * (ld pair; ASM shift-mode hardware, unmodelled, flagged; no shifted op in-span); A |= *AR2 (or);
 * *AR2 = A-low (stl); TC = (cell 0x536 == 6, cmpm); TC clear returns (rc ntc). Runs SUB_059C; AR2 = 5
 * (calld delay, runs first); delayed tail into SUB_2262 (C-bound). AR2 caller-live but overwritten before
 * any read; AR3/BRC set in-span. Entry: exterior call @0x2DEA (PROM).
 */
extern void sub_059C(void);
extern void frag_22CF(void);
extern void sub_2262(void);

void frag_22CF(void)
{
    int *ar1;

    ar1 = (int *)2162;                                     /* stm #2162,ar1 */
    *ar1 = 0;                                                /* st #0,*ar1 */
    *(volatile int *)0x29 |= 8;                              /* orm #8,*(0x29) */
    *(volatile int *)0x29 &= -9;                             /* andm #-9 (net clear) */
    /* ret @22D9 */
}

void sub_2289(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int brc;
    int taken;
    int i;

    sub_059C();                                            /* call 0x59c (RAM) */
    a = (long)(unsigned)*(volatile int *)0x87B;            /* ldu *(0x87b),a */
    a = a - (long)(unsigned)*(volatile int *)0x87E;        /* sub *(0x87e),a */
    a = a - 2048;                                          /* sub #2048,a */
    b = 0;                                                 /* ld #0,b */
    if (a == 0)                                            /* bc 0x22b4,aeq */
        goto l22b4;
    a = (long)(unsigned)*(volatile int *)0x87E;            /* ldu *(0x87e),a */
    a = a + 2048;                                          /* add #2048,a */
    ar2 = (int *)(long)(a & 0xFFFF);                       /* stlm a,ar2 */
    b = (long)(unsigned)*(volatile int *)0x87D;            /* ldu *(0x87d),b */
    if (b == 0)                                            /* bc 0x22b4,beq */
        goto l22b4;
    a = (long)(unsigned)*(volatile int *)0x87F;            /* ldu *(0x87f),a */
    a = a - b;                                             /* sub a,b */
    if (a >= 0)                                            /* bc 0x22a5,bgeq */
        goto l22a5;
    a = (long)(unsigned)*(volatile int *)0x87D;            /* ldu *(0x87d),a */
    b = 0;                                                 /* ld #0,b */
l22a5:
    a = a - 1;                                             /* sub #1,a */
    brc = (int)(a & 0xFFFF);                               /* stlm a,brc */
    a = (long)(unsigned)*(volatile int *)0x87B;            /* ldu *(0x87b),a */
    ar3 = (int *)(long)(a & 0xFFFF);                       /* stlm a,ar3 */
    for (i = 0; i <= brc; i++) {                          /* stm #imm,brc; rptb 0x22ae */
        a = (long)(unsigned)*ar2++;                         /* ldu *ar2+,a */
        *ar3++ = (int)(a & 0xFFFF);                        /* stl a,*ar3+ */
    }
    a = (long)ar3;                                         /* ldm ar3,a (register value) */
    *(volatile int *)0x87D = (int)(b & 0xFFFF);            /* mvmd bl,0x87d */
    *(volatile int *)0x87B = (int)(a & 0xFFFF);            /* mvmd al,0x87b */
l22b4:
    a = (long)*(volatile int *)0x872;                    /* ld *(0x872),a */
    a ^= 4L;                                               /* xor #4,a */
    frag_22CF();                                           /* call 0x22cf */
    if (a != 0)                                            /* bc 0x22bd,aeq (fallthrough) */
        return;
l22bd:
    ar2 = (int *)1334;                                     /* stm #1334,ar2 */
    ar2++;                                                 /* ld *ar2+,asm (step; ASM dead, flagged) */
    a = 1;                                                 /* ld #1,a */
    /* ld a,asm (ASM shift-mode hardware, unmodelled, flagged) */
    a |= (long)(unsigned)*ar2;                             /* or *ar2,a */
    *ar2 = (int)(a & 0xFFFF);                              /* stl a,*ar2 */
    taken = (*(volatile int *)0x536 == 6) != 0;            /* cmpm *(0x536),#6 */
    if (!taken)                                            /* rc ntc */
        return;
    sub_059C();                                            /* call 0x59c (RAM) */
    ar2 = (int *)5;                                        /* calld delay: stm (runs first) */
    sub_2262();                                            /* calld 0x2262 */
    /* ret @22CE */
    (void)taken;
}
