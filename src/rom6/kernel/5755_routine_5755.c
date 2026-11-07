/* ROM6 0x5755 ROUTINE_5755 -- 25w.
 * Verified encoding: src/rom6/kernel/5755_routine_5755.asm (recombine MATCH).
 * ORIGIN 0x5755
 * EXPECT: F074 059C 11F8 250F F330 00F0 F210 0030 FC45 F210 0010 F844 576E 10F8 2642 08F8 0915 FC44 F274 6993 7711 0916 F845 5785 FC00
 *
 * Intent: Masked compare with out-of-span gates. Runs 0x59C; B = cell 0x250F AND 240 (live-in B dead); A = B - 48 (sub, dst = src minus operand per ti-c54x op_sub); zero skips the A = B - 16 recompute (rc aeq); nonzero remainder jumps away (bc 0x576e,aneq: target bytes 11F8 250F F210 0051 F845, forward extern, no C binding yet, per convention). Else A = cell 0x2642 minus cell 0x915; AR1 = 2326 always (calld delay slot); nonzero skips the 0x6993 call (rc aneq, exact), zero runs it then jumps away (bc 0x5785,aeq: target bytes 11F8 250F F330 00F0 7711, forward extern); nonzero-after-calld falls to RET.
 */
extern void sub_059C(void);
extern void sub_6993(void);
extern void frag_576E(void);
extern void frag_5785(void);

static int *G_AR1;

void routine_5755(void)
{
    int a;
    int b;
    sub_059C();                                  /* call 0x59c */
    b = *(volatile int *)0x250F & 240;       /* ld, and */
    a = b - 48;                                  /* sub #48,b,a */
    if (a != 0) {                                /* rc aeq */
        a = b - 16;                              /* sub #16,b,a */
        if (a != 0) {                            /* bc 0x576e,aneq */
            frag_576E();                         /* away, unbound */
            return;
        }
    }
    a = *(volatile int *)0x2642 -
        *(volatile int *)0x915;              /* ld, sub */
    G_AR1 = (int *)2326;                         /* calld delay slot: always */
    if (a == 0)                                  /* rc aneq */
        sub_6993();                              /* calld 0x6993 */
    if (a == 0) {                                /* bc 0x5785,aeq */
        frag_5785();                             /* away, unbound */
        return;
    }
    /* ret */
}
