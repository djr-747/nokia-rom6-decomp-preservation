/* ROM6 0x2C8A RING_ARITH_2C8A -- 43w.
 * Verified encoding: src/rom6/boot/2c8a_ring_arith_2c8a.asm (recombine MATCH).
 * ORIGIN 0x2C8A
 * EXPECT: 11F8 08E5 6FF8 08E4 0E20 F846 2C93 F000 0064 4915 F300 0003 F3FF F620 F846 2CB5 E900 61F8 3EC8 0002 FC20 61F8 054D 000C FC20 7712 2F00 7692 0401 7692 0174 7682 1200 E905 7712 2F00 E814 7710 00F4 F074 93CE E900 FC00
 *
 * Intent: Ring-report arithmetic gate with dual RC guards and st block build. B = cell 0x8E5 (ld); A = B -
 * cell 0x8E4 (sub Smem,b,a, 2D8F dual precedent); A > 0 adds 100 (bc agt/add). B = AR5-live (ldm ar5,b,
 * caller-live, unbound, flagged); B += 3 (add); B <<= 1 logical (sftl b,-1); A -= B (sub b,a); A > 0
 * tail-joins worker_2CB5 (bc agt; asm-only span, forward extern). B = 0 (ld); TC = cell 0x3EC8 bit 1 clear
 * returns (bitf/rc ntc); TC = cell 0x54D bit 2 clear returns (bitf/rc ntc). AR2 = 12032 (stm); cells
 * 12032-12034 = 1025/372/4608 (st block); B = 5; AR2 = 12032; A = 20; AR0 = 244 (presets); runs dark
 * SUB_93CE (forward extern); B = 0; return. Entry: fall-through from the 2C88 ring gate; no other exterior
 * callers, entry unconfirmed, flagged.
 */
extern void frag_2CB5(void); /* joins 2cb5_worker_2cb5; see docs/evidence/extern-triage.md */
extern void sub_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */

void frag_2C8A(int ar5_live)
{
    long a;
    long b;
    int *ar2;


    b = (long)*(volatile int *)0x8E5;                      /* ld *(0x8e5),b */
    a = b - (long)*(volatile int *)0x8E4;                  /* sub *(0x8e4),b,a */
    if (a > 0)                                             /* bc 0x2c93,agt */
        a += 100;                                          /* add #100,a */
    b = (long)ar5_live;                                    /* ldm ar5,b (caller-live) */
    b += 3;                                                /* add #3,b */
    b = (unsigned long)b << 1;                             /* sftl b,-1 (logical) */
    a = a - b;                                             /* sub b,a */
    if (a > 0) {                                           /* bc 0x2cb5,agt */
        frag_2CB5();                                       /* (2CB5 interior) */
        return;
    }
    b = 0;                                                 /* ld #0,b */
    if ((*(volatile int *)0x3EC8 & 2) == 0)                /* bitf; rc ntc */
        return;
    if ((*(volatile int *)0x54D & 12) == 0)                /* bitf; rc ntc */
        return;
    ar2 = (int *)12032;                                    /* stm #12032,ar2 */
    *ar2++ = 1025;                                         /* st #1025,*ar2+ */
    *ar2++ = 372;                                          /* st #372,*ar2+ */
    *ar2 = 4608;                                           /* st #4608,*ar2 */
    b = 5;                                                 /* ld #5,b */
    ar2 = (int *)12032;                                    /* stm #12032,ar2 */
    a = 20;                                                /* ld #20,a */
    /* stm #244,ar0 (preset, dark callee may read, flagged) */
    sub_93CE();                                            /* call 0x93ce (dark) */
    b = 0;                                                 /* ld #0,b */
    /* ret @2CB4 */
}
