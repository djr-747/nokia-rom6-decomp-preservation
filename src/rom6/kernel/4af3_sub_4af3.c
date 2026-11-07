/* ROM6 0x4AF3 SUB_4AF3 -- 19w.
 * Verified encoding: src/rom6/kernel/4af3_sub_4af3.asm (recombine MATCH).
 * ORIGIN 0x4AF3
 * EXPECT: F074 059E 60F8 250F 0022 F820 4B07 F7BB 74F8 000B 0038 F330 0008 F84D 4B06 F6BB F4E1 F073 4AF3
 *
 * Intent: Port 56 idle-poll loop. Runs 0x59E (dark, forward extern); cell 0x250F != 34 jumps away to dark 0x4B07 (bc ntc, forward extern). Else locks INTM (ssbx, hardware state) and polls port 56 BL (portr 56,*(0xb): BL alias) until bit 3 clears (and #8,b; bc 0x4b06,beq to FRAG_4B06: has .asm, no C yet, forward extern); each set-bit pass unlocks (rsbx, hardware state), idles one cycle (idle 1, extern op per convention), and loops (b 0x4af3 self-edge). Bound 4AF3-4B05.
 */
extern void sub_059E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_4B07(void); /* joins 4b06_frag_4b06 interior @+0x1; see docs/evidence/extern-triage.md */
extern int port_read_56(void);                                        /* HW port 56 (HPI/pa56 poll per 2baa span); no ROM definition */
extern void frag_4B06(void);
extern void idle_1(void);                                             /* IDLE 1 (per 4af3 span); no ROM definition */

void sub_4AF3(void)
{
    int b;
    sub_059E();                                  /* call 0x59e */
    if (*(volatile int *)0x250F != 34) {         /* cmpm, bc ntc */
        frag_4B07();                             /* away, dark */
        return;
    }
    for (;;) {                                   /* b 0x4af3 self-edge */
        /* ssbx st1,intm: INTM lock (hardware state) */
        b = port_read_56();                      /* portr 56,*(0xb) */
        *(volatile int *)0xB = b;            /* BL alias write */
        b &= 8;                                  /* and #8,b */
        if (b == 0) {                            /* bc 0x4b06,beq */
            frag_4B06();                         /* away, unbound C */
            return;
        }
        /* rsbx st1,intm: unlock (hardware state) */
        idle_1();                                /* idle 1 */
    }
}
