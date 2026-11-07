/* ROM6 0x9C4D WRAP_9C4D -- 20w.
 * Verified encoding: src/rom6/kernel/9c4d_wrap_9c4d.asm (recombine MATCH).
 * ORIGIN 0x9C4D
 * EXPECT: 7312 21FB 4914 68F8 20FF 7FFF F84D 9C58 69F8 20FF 8000 F7BB 4916 F784 01F8 20FE 81F8 20FE F6BB FC00
 *
 * Intent: Flag wrap with guarded negate. Cell0x21FB = AR2-value
 * (mvmd); B = AR4-value; cell0x20FF bit15 cleared (andm); B != 0
 * sets it (bc 0x9c58,beq skips the 3-word orm only, exact);
 * INTM lock (ssbx, hardware state); B = cell0x20FE - AR6-value
 * (ldm + NEG + ADD, op_neg_acc precedent for neg); cell0x20FE =
 * B-low; INTM unlock (rsbx, hardware state); return. Bound 9C4D-9C60.
 */
void wrap_9C4D(int *ar2, int ar4_live, int ar6_live)
{
    long b;
    *(volatile int *)0x21FB = (int)ar2;              /* mvmd ar2,0x21fb */
    b = (long)ar4_live;                              /* ldm ar4,b */
    *(volatile int *)0x20FF &= 32767;                /* andm #-32769... clears bit15 */
    if (b != 0)                                      /* bc 0x9c58,beq (skips orm) */
        *(volatile int *)0x20FF |= 0x8000;           /* orm #-32768,*(0x20ff) */
    /* ssbx st1,intm: INTM lock (hardware state) */
    b = -(long)ar6_live;                             /* ldm ar6,b; neg b */
    b += (long)*(volatile int *)0x20FE;              /* add *(0x20fe),b */
    *(volatile int *)0x20FE = (int)(b & 0xFFFF);     /* stl b,*(0x20fe) */
    /* rsbx st1,intm: INTM unlock (hardware state) */
    /* ret */
}
