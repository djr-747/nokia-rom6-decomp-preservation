/* ROM6 0x389C FRAG_389C + FRAG_38AA -- 45w.
 * Verified encoding: src/rom6/kernel/389c_frag_389c.asm (recombine MATCH).
 * ORIGIN 0x389C
 * EXPECT: F074 062C 61F8 3EC8 0002 F830 3943 61F8 051F 0080 F830 3913 11F8 3E80 F600 61F8 3E7E 0002 F930 38FB 61F8 3E7E 0004 F930 38C9 60F8 0012 0031 F820 38C5 F495 75F8 0008 0031 F495 F495 75F8 0009 0032 6DEA 0002 FF20 8092 8292 FC00
 *
 * Intent: Port-strobe lane with mid-span join, two entries.
 * The 389C entry: runs 0x62C (dark, extern); TC = bit 1 of
 * cell 0x3EC8 (bitf); set tail-calls frag_3943 (bc, dark
 * forward extern, intake unbound) and returns; else TC =
 * bit 7 of cell 0x51F; set tail-calls frag_3913 with live A/AR2 (bc; the
 * 3913 head now has C intent in the 3907 file -- its gosub
 * re-derives A, AR2 threads to its 38AA tail) and returns;
 * else B = cell 0x3E80 (ld) and
 * falls into the 38AA lane. The 38AA entry (from 3907's
 * bd-tail and the fall-through; sled convention): A += B
 * (add Smem, SXM = 1 flagged) with its zero flag latched
 * for the 38C9 call below; TC = bit 1 of cell 0x3E7E
 * (bitf); set runs frag_38FB with the 16-bit A-low
 * (cc 0x38fb,tc -- conditional call, grounded; the int
 * intake narrows A, flagged) and takes its int A-out;
 * TC = bit 2 of cell 0x3E7E; set runs routine_38C9 with
 * the 16-bit A-low, live AR3 and the latched add-zero
 * flag (cc 0x38c9,tc; the entry-Z rides the add per the
 * 38C9 header's Z-preservation note: bitf/cc/call preserve
 * Z) and takes its int A-out; TC = (cell 0x12 == 49)
 * (cmpm, oracle: TC = equality); set runs the two port
 * strokes (portw *(0x8),49 and portw *(0x9),50 as
 * port_write_8/9 extern ops; ports do not touch TC),
 * clear skips them (bc 0x38c5,ntc lands on the mar);
 * AR2 += 2 (mar, linear, no AR0 involved); TC still the
 * cmpm result runs both stores (xc 2,ntc covers stl
 * a,*ar2+ then sth a,*ar2+: LOW then HIGH of A, exact via
 * long) else skips them; return. A is entry-live (dark
 * 062C residue on the top path, flagged) or caller-passed
 * on the 38AA path; AR2/AR3 are caller-live; B is loaded
 * in-span on the top path, caller-passed on the 38AA path.
 * Bound 389C-38C8 (45w; the .asm header's old 41w count is stale).
 */
extern void sub_062C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_3943(void); /* joins 3938_frag_3938 interior @+0xB; see docs/evidence/extern-triage.md */
extern void frag_3913(long a_live, int *ar2_in);
extern int frag_38FB(int a_live);
extern int routine_38C9(int a_live, int *par3, int z_live);
extern void port_write_8(int v);                                      /* HW port 8 (RF per 389c/3EE1 spans); no ROM definition */
extern void port_write_9(int v);                                      /* HW port 9 (RF per 389c/3d79 spans); no ROM definition */

void frag_389C(long a_live, int *ar2_in, int *ar3_live)
{
    long b;
    sub_062C();                                      /* call 0x62c */
    if ((*(volatile int *)0x3EC8 & 2) != 0) {        /* bitf; bc tc */
        frag_3943();
        return;
    }
    if ((*(volatile int *)0x51F & 128) != 0) {       /* bitf; bc tc */
        frag_3913(a_live, ar2_in);
        return;
    }
    b = (long)*(volatile int *)0x3E80;               /* ld *(0x3e80),b */
    frag_38AA(a_live, b, ar2_in, ar3_live);
}

void frag_38AA(long a_live, long b_live, int *ar2_in, int *ar3_live)
{
    int *ar2 = ar2_in;
    long a = a_live + b_live;                        /* add b,a (SXM flagged) */
    int z_add = (a == 0);                            /* zero flag rides to 38C9 */
    long b = b_live;
    if ((*(volatile int *)0x3E7E & 2) != 0)          /* bitf; cc tc */
        a = frag_38FB((int)(a & 0xFFFF));
    if ((*(volatile int *)0x3E7E & 4) != 0)          /* bitf; cc tc */
        a = routine_38C9((int)(a & 0xFFFF), ar3_live, z_add);
    if ((*(volatile int *)0x12 & 0xFFFF) == 49) {    /* cmpm (TC = equality) */
        /* nop */
        port_write_8(49);                            /* portw *(0x8),49 */
        /* nop; nop */
        port_write_9(50);                            /* portw *(0x9),50 */
    }
    /* bc 0x38c5,ntc: join */
    ar2 += 2;                                        /* mar *+ar2(0x2) */
    if ((*(volatile int *)0x12 & 0xFFFF) == 49) {    /* xc 2,ntc (TC live) */
        *ar2++ = (int)(a & 0xFFFF);                  /* stl a,*ar2+ */
        *ar2++ = (int)(((unsigned long)a >> 16) & 0xFFFF);  /* sth a,*ar2+ */
    }
    /* ret */
    (void)b;
}
