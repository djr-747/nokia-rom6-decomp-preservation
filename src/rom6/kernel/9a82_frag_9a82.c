/* ROM6 0x9A82 FRAG_9A82 -- 61w message-shape filter with stack handoff.
 * Verified encoding: src/rom6/kernel/9a82_frag_9a82.asm (recombine MATCH).
 * ORIGIN 0x9A82
 * EXPECT: F074 0710 68F8 20FF FFDF E878 F7BB 1183 F487 F520 4A12 4A08 61F8 20FF 8000 8183 F540 E800 FD30 E801 F495 F495 4A08 F6BB 7713 2F00 8915 61F8 20FF 8000 F820 9ABF F77F F808 9AA8 68F8 20FF 7FFF 61F8 20FF 8000 44D2 F310 0001 891A F84B 9ABA F072 9AB7 1AD2 6F93 0C98 F0E8 F0E8 FD30 6DC2 FF20 6F83 0C98 F073 9AD2
 *
 * Intent: Head entry via 6x pre-span bc (9A58-9A7C), single entry
 * (all interior joins verified in-span). AR2/AR3 caller-live dark
 * (params, 8b9d precedent). Runs dark SUB_0710 (low-zone mini-kernel,
 * no symbol, opaque). Cell 0x20FF &= -33 (andm). A = 120; INTM = 1
 * (ssbx, hardware no-C-form precedent). B = *AR3; A = min(B,A) signed
 * (min a dst=A, 66c5 signed family); B -= A (sub; borrow clobbered
 * unread by the later sfta, noted). Push AR2 value, A-low, A-low (3
 * words stack-carried to the 9AD2 tail which pops al/bl/ar2 per its C;
 * the pooled-9ABF exit leaves them, flagged). TC = bit15 of cell
 * 0x20FF; *AR3 = B-low; B = A; A = 0, or 1 when TC set (xc 1 over the
 * 1-word ld; nops settle, comments). INTM = 0 (rsbx). AR3 = 12032;
 * AR5 = B-low. TC re-read; clear tail-exits to pooled 9ABF (bc ntc;
 * no C entry, effects dark). C = B-bit0 then B >>= 1 arithmetic
 * (sfta, 59dc shift-out precedent); C set keeps bit15 cleared (andm;
 * bc nc skips it when clear). TC re-read (9AA8 join). A = *AR2++ << 16
 * (ld shift, +% steps linear with circular flagged per 25f2); B--;
 * BRC = B-low. B < 0 skips the rptb (bc blt); else (B-low+1)x: A |=
 * (unsigned)*AR2++ (or Smem zero-extends per 2289); *AR3++ = A>>8
 * (stl-shift, 315f/2ed6 idiom); A <<= 8 twice (sftl). TC set steps
 * AR2 back (xc mar); TC clear stores *AR3 = A>>8 (xc stl); tail-calls
 * frag_9AD2 (b; pops the 3 stack words). T untouched (dark, noted).
 * Out cells/A/B/ARs/TC/C; AR2 consumed. EXPECT from the image.
 */
extern void sub_0710(void); /* dark, no symbol (low-zone mini-kernel) */
extern void frag_9AD2(void);
/* bc 0x9abf: pooled, no C entry (see Pool note in 9abf_frag_9abf.c) */

void frag_9A82(int *ar2_in, int *ar3_in)
{
    long a;
    long b;
    int c;
    int tc;
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    int *ar5;
    int stk_ar2;  /* pshm ar2 (stack-carried to 9AD2) */
    int stk_a1;   /* pshm al */
    int stk_a2;   /* pshm al */
    long n;
    int i;

    sub_0710();                                              /* call 0x710 */
    *(volatile int *)0x20FF &= -33;                          /* andm #-33,*(0x20ff) */
    a = 120L;                                                /* ld #120,a */
    /* ssbx st1,intm (hardware, no C form) */
    b = (long)*ar3;                                          /* ld *ar3,b */
    if (b < a)                                               /* min a (dst=A, signed) */
        a = b;
    b -= a;             /* sub a,b (borrow clobbered unread by sfta below, noted) */
    stk_ar2 = (int)(long)ar2;                                /* pshm ar2 */
    stk_a1 = (int)(a & 0xFFFFL);                             /* pshm al */
    tc = ((*(volatile int *)0x20FF & 0x8000) != 0);          /* bitf *(0x20ff),#-32768 */
    *ar3 = (int)(b & 0xFFFFL);                               /* stl b,*ar3 */
    b = a;                                                   /* ld a,b */
    a = 0L;                                                  /* ld #0,a */
    if (tc)                                                  /* xc 1,tc */
        a = 1L;                                              /* ld #1,a */
    /* nop; nop (settles, no state) */
    stk_a2 = (int)(a & 0xFFFFL);                             /* pshm al */
    /* rsbx st1,intm (hardware, no C form) */
    ar3 = (int *)(long)12032;                                /* stm #12032,ar3 */
    ar5 = (int *)(long)(b & 0xFFFFL);                        /* stlm b,ar5 */
    tc = ((*(volatile int *)0x20FF & 0x8000) != 0);          /* bitf (re-read) */
    if (!tc) {                                               /* bc 0x9abf,ntc */
        /* b 0x9abf (pooled; 3 pushed words unpopped there, flagged) */
        (void)stk_ar2;
        (void)stk_a1;
        (void)stk_a2;
        return;
    }
    c = (int)(b & 1L);                                       /* sfta b,-1 (C = shift-out) */
    b >>= 1;
    if (c != 0)                                              /* bc 0x9aa8,nc not taken */
        *(volatile int *)0x20FF &= 32767;                    /* andm #32767,*(0x20ff) */
    tc = ((*(volatile int *)0x20FF & 0x8000) != 0);          /* bitf @9aa8 */
    a = (long)*ar2 << 16;                                    /* ld *ar2+%,16,a */
    ar2++;                                                   /* +% (circular flagged) */
    b -= 1L;                                                 /* sub #1,b */
    if (b >= 0) {                                            /* bc 0x9aba,blt not taken */
        n = (b & 0xFFFFL) + 1;                               /* stlm b,brc; rptb count */
        for (i = 0; i < n; i++) {                            /* rptb 0x9ab7 */
            a |= (long)(unsigned)*ar2++;                     /* or *ar2+%,a */
            *ar3++ = (int)((a >> 8) & 0xFFFF);               /* stl a,-8,*ar3+ */
            a <<= 8;                                         /* sftl a,8 */
            a <<= 8;                                         /* sftl a,8 */
        }
    }
    if (tc)                                                  /* xc 1,tc */
        ar2--;                                               /* mar *ar2-% */
    if (!tc)                                                 /* xc 2,ntc */
        *ar3 = (int)((a >> 8) & 0xFFFF);                     /* stl a,-8,*ar3 */
    frag_9AD2();                                             /* b 0x9ad2 (tail; pops 3 stack words) */
}
