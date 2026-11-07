/* ROM6 0x9A50 ROUTINE_9A50 -- 32w.
 * Verified encoding: src/rom6/kernel/9a50_routine_9a50.asm (recombine MATCH).
 * ORIGIN 0x9A50
 * EXPECT: F074 05D2 7713 20FE 1083 FC47 10F8 2202 F844 9A82 61F8 20FF 0200 F820 9A70 1083 F010 005F F842 9A82 61F8 20FF 0020 F830 9A82 12F8 20FB F010 0003 F842 9A82 FC00
 *
 * Intent: Guarded identity-lane checks. Runs 0x5D2 (dark,
 * extern); AR3 = 8446 (entry AR3 clobbered); A = *AR3;
 * rc aleq (grounded: return iff A <= 0); A = cell 0x2202;
 * nonzero tail-enters frag_9A82 with live A (forward extern,
 * 89b3 precedent); cell 0x20FF bit 9 clear tail-enters
 * frag_9A70 with AR3 (= 8446); A = *AR3 - 95 (sub lk
 * grounded); non-negative tail-enters 9A82; cell 0x20FF
 * bit 5 set tail-enters 9A82; A = unsigned cell 0x20FB
 * (ldu, 3691 precedent) - 3; non-negative tail-enters 9A82;
 * else return. BITF single-bit masks read TC exactly
 * (mask == test, both senses coincide). Bound 9A50-9A6F.
 */
extern void sub_05D2(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_9A82(long a_live); /* joins 9a82_frag_9a82; see docs/evidence/extern-triage.md */
extern void frag_9A70(int *par3);

void routine_9A50(void)
{
    int *ar3 = (int *)8446;                          /* stm #8446,ar3 */
    long a;
    sub_05D2();                                      /* call 0x5d2 */
    a = (long)*ar3;                                  /* ld *ar3,a */
    if (a <= 0)                                      /* rc aleq */
        return;
    a = (long)*(volatile int *)0x2202;               /* ld *(0x2202),a */
    if (a != 0) {                                    /* bc 0x9a82,aneq */
        frag_9A82(a);
        return;
    }
    if ((*(volatile int *)0x20FF & 512) == 0) {      /* bitf; bc ntc */
        frag_9A70(ar3);
        return;
    }
    a = (long)*ar3;                                  /* ld *ar3,a */
    a -= 95;                                         /* sub #95,a */
    if (a >= 0) {                                    /* bc 0x9a82,ageq */
        frag_9A82(a);
        return;
    }
    if ((*(volatile int *)0x20FF & 32) != 0) {       /* bitf; bc tc */
        frag_9A82(a);
        return;
    }
    a = (unsigned long)(unsigned)*(volatile int *)0x20FB;  /* ldu */
    a -= 3;                                          /* sub #3,a */
    if (a >= 0) {                                    /* bc 0x9a82,ageq */
        frag_9A82(a);
        return;
    }
    /* ret */
}
