/* ROM6 0xACF4 ROUTINE_ACF4 -- 25w.
 * Verified encoding: src/rom6/kernel/acf4_routine_acf4.asm (recombine MATCH).
 * ORIGIN 0xACF4
 * EXPECT: 61F8 3E7E 0004 F820 ACFD 8292 8092 F073 AD0A 61F8 3E7E 0002 F830 AD06 8292 8292 F073 AD0A 7715 3E81 E5B8 E5B8 F074 AE22 FC00
 *
 * Intent: Three-way store select. A is live-in, stored 32-bit (high then low: sth src(31:16) per ti-c54x op_sth, then stl) through live-in AR2 when bit 2 of cell 0x3E7E is clear (bc 0xacfd,ntc skips the ACF4 store pair, landing on the bit-1 test). Else jumps to the call (b 0xad0a, in-span). Bit 1 set stores high twice (bc 0xad06,tc skips the second... lands on the double-high pair); clear jumps to the call (b 0xad0a). Else AR5 = 16001, two moves from there through AR2 (mvdd), then call 0xAE22, return. BITF any-bit TC per ti-c54x op_bitf. Bound ACF4-AD0C.
 */
void routine_ACF4(int a_live, int **ppar2)
{
    int *ar2 = *ppar2;
    if ((*(volatile int *)0x3E7E & 4) == 0)      /* bitf, bc ntc */
        goto L_ACFD;
    *ar2++ = (a_live >> 16) & 0xFFFF;            /* sth a,*ar2+ */
    *ar2++ = a_live & 0xFFFF;                    /* stl a,*ar2+ */
    goto L_CALL;                                 /* b 0xad0a */
L_ACFD:
    if ((*(volatile int *)0x3E7E & 2) == 0) {    /* bitf, bc tc */
        *ar2++ = (a_live >> 16) & 0xFFFF;        /* sth a,*ar2+ */
        *ar2++ = (a_live >> 16) & 0xFFFF;        /* sth a,*ar2+ */
        goto L_CALL;                             /* b 0xad0a */
    }
    {
        int *src = (int *)16001;                 /* stm #16001,ar5 */
        *ar2++ = *src++;                         /* mvdd *ar5+,*ar2+ */
        *ar2++ = *src++;                         /* mvdd *ar5+,*ar2+ */
    }
L_CALL:
    *ppar2 = ar2;
    /* call 0xae22 (forward extern, unbound) */
    /* ret */
}
