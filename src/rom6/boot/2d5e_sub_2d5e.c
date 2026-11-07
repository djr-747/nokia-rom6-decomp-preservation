/* ROM6 0x2D5E SUB_2D5E -- 45w.
 * Verified encoding: src/rom6/boot/2d5e_isr_2d5e.asm (recombine MATCH).
 * ORIGIN 0x2D5E
 * EXPECT: F074 0626 61F8 054D 000C F820 2D7F 4A12 4A13 7713 2F00 7693 0401 10F8 0012 F130 00FF F340 0100 8193 F030 FF00 8083 E905 7712 2F00 E814 7710 00F4 F074 93CE 8A13 8A12 1083 F844 2D8B 4812 8083 69F8 0029 0008 68F8 0029 FFF7 FC00
 *
 * Intent: Frame-tick ISR head (9x calld sites image-wide: 50F9/5CE8/
 * 5E78/5ED5/7128/978A/21CD/2267 and more; C callers 50B2/56A2 via
 * this signature). Runs dark SUB_0626 (no symbol, opaque). TC =
 * (*(0x54D) & 12) != 0 (bitf, 5d38 polarity); clear joins the 2D7F
 * lane (bc 0x2d7f,ntc; mid-span in-label L2D7F below). Snapshot
 * lane: pshm ar2/ar3 (balanced by the popm pair; entry values
 * preserved, never read through the saved copies -- comments only
 * per the 5d38 dead-lane precedent). AR3 = 12032 local (stm; dies
 * at popm): MEM[12032] = 1025 (st). A = ST1 (*(0x12), volatile MMR
 * read); B = (A & 255) | 256 (and/or); MEM[12033] = B-low (stl);
 * A &= -256 (and #-256); MEM[12034] = A-low (stl). Call setup
 * B = 5, AR2 = 12032, A = 20, AR0 = 244 (stm/ld immediates); B/AR0
 * dead in 93ce's C contract (opaque, flagged). TC-result =
 * msg_classify_by_caller(12032-ptr, SP-entry, 20) (linked C;
 * SP-entry dark ISR context, unbound local; int return ignored
 * in-span, TC-out not carried -- caller liveness unbound, flagged).
 * popm restores AR3/AR2. L2D7F lane (AR3/AR2 = entry values):
 * A = *AR3-entry (ld); nonzero exits to FRAG_2D8B (bc 0x2d8b,aneq;
 * asm-only, forward extern). Else A = AR2-entry address value
 * (ldm ar2,a: a = (long)par2 per the 50B2 precedent);
 * MEM[AR3-entry] = A-low (stl); cell 0x29 |= 8 then &= ~9 (orm
 * then andm #-9: two real strokes -- bit0 cleared, bit3 restored;
 * NOT a net nop). return. A/B dead after (void).
 */
extern void sub_0626(void);                          /* dark, no symbol */
extern int msg_classify_by_caller(int *par2, int *sp_live, long a_live);
extern void frag_2D8B(void);                         /* asm-only, forward extern */

void sub_2D5E(int *par2, int *par3)
{
    long a;
    long b;
    int *ar3;
    int *sp;                                         /* unbound: entry SP */
    int tc_result;
    sub_0626();                                      /* call 0x626 */
    if ((*(volatile int *)0x54D & 12) == 0)          /* bitf; bc 0x2d7f,ntc */
        goto l2d7f;
    /* pshm ar2/ar3 (balanced by popm; caller-live, comments only) */
    ar3 = (int *)(long)12032;                        /* stm #12032,ar3 (local) */
    *ar3++ = 1025;                                   /* st #1025,*ar3+ */
    a = (long)*(volatile int *)0x12;                 /* ld *(0x12),a (ST1) */
    b = a & 255L;                                    /* and #255,a,b */
    b |= 256L;                                       /* or #256,b */
    *ar3++ = (int)(b & 0xFFFF);                      /* stl b,*ar3+ */
    a &= -256L;                                      /* and #-256,a */
    *ar3 = (int)(a & 0xFFFF);                        /* stl a,*ar3 */
    b = 5;                                           /* ld #5,b (call setup, opaque) */
    /* stm #12032,ar2 -> (int *)(long)12032 below; ld #20,a -> 20L; stm #244,ar0 (opaque) */
    tc_result = msg_classify_by_caller((int *)(long)12032, sp, 20L);
    (void)tc_result;                                 /* TC result ignored in-span */
    (void)b;
    /* popm ar3/ar2 (restore entry values) */
l2d7f:
    a = (long)*par3;                                 /* ld *ar3,a (entry AR3) */
    if (a != 0) {                                    /* bc 0x2d8b,aneq */
        frag_2D8B();
        return;
    }
    a = (long)par2;                                  /* ldm ar2,a (entry AR2 value) */
    *par3 = (int)(a & 0xFFFF);                       /* stl a,*ar3 */
    *(volatile int *)0x29 |= 8;                      /* orm #8,*(0x29) */
    *(volatile int *)0x29 &= -9;                     /* andm #-9,*(0x29) */
}
