/* ROM6 0x71D8 SCALE_3EB8_LEAF -- 16w.
 * Verified encoding: src/rom6/kernel/71d8_scale_3eb8_leaf.asm (recombine MATCH).
 * ORIGIN 0x71D8
 * EXPECT: F074 0598 61F8 3EB5 0010 FC20 44F8 0578 40F8 0585 31F8 3EB8 F778 0183 8183 FC00
 *
 * Intent: Scaled product plus post. Runs 0x598; when bit 4 of cell 0x3EB5 is set (bitf any-bit TC per ti-c54x op_bitf; rc ntc skips only when clear), A = cell 0x578 << 16, else A is live-in; always A -= cell 0x585 << 16. B = cell 0x3EB8 times A-high (MPYA Smem overwrites B per ti-c54x op_mpya_smem, T untouched); B >>= 8 (sfta, 40-bit); B += *AR3 (live-in); store low word back, return it.
 */
extern void sub_0598(void);

int scale_3EB8_leaf_71D8(int a_live, int *par3)
{
    long a;
    long b;
    sub_0598();                                  /* call 0x598 */
    if ((*(volatile int *)0x3EB5 & 16) != 0)     /* bitf, rc ntc */
        a = ((long)*(volatile int *)0x578 << 16); /* ld *(0x578),16,a */
    else
        a = a_live;                              /* ld skipped */
    a -= ((long)*(volatile int *)0x585 << 16); /* sub *(0x585),16,a */
    b = (long)*(volatile int *)0x3EB8 * (int)(a >> 16); /* mpya */
    b >>= 8;                                     /* sfta b,-8 */
    b += *par3;                                 /* add *ar3,b */
    *par3 = (int)b;                              /* stl b,*ar3 */
    return (int)b;                               /* ret */
}
