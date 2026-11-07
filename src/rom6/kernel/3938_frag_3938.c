/* ROM6 0x3938 FRAG_3938 -- 67w scaled port kick on A range.
 * Verified encoding: src/rom6/kernel/3938_frag_3938.asm (recombine MATCH).
 * ORIGIN 0x3938
 * EXPECT: F110 007D F84E 394E F0E2 F000 4EC0 7713 0001 F073 395E F110 007D F84E 3957 F0E2 F000 4EE8 7713 0001 F073 395E F010 0200 F0E1 F000 4E0E 7713 0000 F073 395E F010 0200 F0E1 F000 4C2E 7713 0000 F074 05A0 F55F F330 003F F030 FF80 F2A0 F0E2 F040 0003 F0EA 60F8 0012 0031 F820 397B F495 75F8 0008 0031 F495 F495 75F8 0009 0032 6DEA 0002 FC00
 *
 * Intent: B = A-live-in - 125 (sub, A kept). B > 0 detours to 0x394E (bc
 * bgt), else A = (A << 2) + 20160, AR3 = 1, rejoins 0x395E. At 0x394E the
 * same B = A - 125 is recomputed (A untouched, so the second bgt to 0x3957
 * repeats the first verdict; transcribed literally, the 20200 arm kept as
 * specified). B > 0 runs A = ((A - 512) << 1) + 19982, AR3 = 0, rejoins;
 * else A = (A << 2) + 20200, AR3 = 1, rejoins. Merge at 0x395E: runs dark
 * SUB_05A0 (call, forward extern, void per 2E64/8413 precedent). B = A >> 1
 * (ld a,-1,b, arithmetic); B &= 63; A &= -128 (0xFF80); A |= B; A <<= 2;
 * A |= 3; A <<= 10 (40-bit sftl chain, long arithmetic). Cell 0x12 == 49
 * (cmpm, TC-only) runs the port pair: value 49 to port 1 from DP alias 8,
 * value 50 to port 2 from DP alias 9 (portw, extern ops; nop settles);
 * mismatch (bc ntc) skips to 0x397B. AR2-entry += 2 (mar, bump rides to
 * caller; entry value unused in-span) and returns. A, AR2 entry-live; AR3
 * the only register live-out. Bound 3938-397A (exit FC00@397A).
 */
extern void sub_05A0(void);
extern void portw_alias08_port49(void);
extern void portw_alias09_port50(void);

void frag_3938(int a_live, int *par2, int *par3_out)
{
    long a = (long)a_live;
    long b = a - 125L;                         /* sub #125,a,b */

    if (b > 0) {                               /* bc 0x394e,bgt */
        b = a - 125L;                          /* sub #125,a,b (recomputed) */
        if (b > 0) {                           /* bc 0x3957,bgt */
            a = ((a - 512L) << 1) + 19982L;    /* sub/sftl/add arm */
            *par3_out = 0;                     /* stm #0,ar3 */
        } else {
            a = (a << 2) + 20200L;             /* sftl/add arm */
            *par3_out = 1;                     /* stm #1,ar3 */
        }
    } else {
        a = (a << 2) + 20160L;                 /* sftl/add arm */
        *par3_out = 1;                         /* stm #1,ar3 */
    }
    /* 0x395e merge */
    sub_05A0();                                /* call 0x5a0 */
    b = a >> 1;                                /* ld a,-1,b (arithmetic) */
    b &= 63L;                                  /* and #63,b */
    a &= -128L;                                /* and #-128,a (mask 0xFF80) */
    a |= b;                                    /* or b,a */
    a <<= 2;                                   /* sftl a,2 */
    a |= 3L;                                   /* or #3,a */
    a <<= 10;                                  /* sftl a,10 */
    if (*(volatile int *)0x12 == 49) {         /* cmpm; bc 0x397b,ntc */
        /* nop; portw *(0x8),49; nop; nop; portw *(0x9),50 */
        portw_alias08_port49();
        portw_alias09_port50();
    }
    /* 0x397b: mar *+ar2(0x2) */
    *par2 += 2;
    /* ret */
}
