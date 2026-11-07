/* ROM6 0x771A PORT8_NORM_LOOP -- 21w.
 * Verified encoding: src/rom6/rf/771a_port8_norm_loop.asm (recombine MATCH).
 * ORIGIN 0x771A
 * EXPECT: 10F8 2F06 F030 FFFF 7EF8 0008 7308 0009 F48F 6BF8 000E FFFF F074 7967 E5A8 E568 6E8F 771A 6DEB FFE0 FC00
 *
 * Intent: Port-8 normalize loop (callers in 7522). Per pass: A =
 * *(0x2F06) sign-extended (ld); A &= 0xFFFF (and #-1,a, zero-extend
 * rule). reada *(0x8): Dmem[cell 0x8] <- Pmem[A] (PAR <- A, AFAB
 * ground truth; 2-word 7EF8 0008 form). Dmem[cell 0x9] = A-low
 * (mvmd al,0x9). A <<= T (norm a, signed-T shift per op_norm_acc;
 * T entry-dark explicit param, 40-bit/OVM flagged). MEM[0xE] -= 1
 * (addm #-1). Runs pooled SUB_7967 (forward extern void; A/B/AR
 * live-ins dark through the callee, A-out is the 7967 residue --
 * dark, void + flagged, not carried). Ping-pong copy *AR2++ =
 * *AR4++ then *AR2++ = *AR4-- (mvdd pair; AR4 net 0 per pass).
 * banzd self-loop on AR7-- (test-then-decrement per op_banz; the
 * mar delay runs every pass including the last, then fall-through
 * to ret). AR3 -= 32 per pass (mar *+ar3(0xffe0), linear). AR2/AR3/
 * AR4 threaded as int** (bfaa precedent); AR7 count + T explicit.
 */
extern void sub_7967(void);                          /* pooled; dark live-ins/outs */
extern int prom_read_word(int prog_addr);            /* Pmem16 read for the reada pair leg */

void frag_771A(int **ar2_io, int **ar3_io, int **ar4_io, int ar7_in, int t_in)
{
    long a;
    int ar7 = ar7_in;
    int t = t_in;
    do {                                             /* banzd 0x771a,*ar7- loop */
        a = (long)*(volatile int *)0x2F06;           /* ld *(0x2f06),a */
        a &= 0xFFFFL;                                /* and #-1,a */
        *(volatile int *)0x8 = prom_read_word((int)a); /* reada *(0x8) */
        *(volatile int *)0x9 = (int)(a & 0xFFFFL);   /* mvmd al,0x9 */
        if (t >= 0) {                                /* norm a */
            a <<= t;
        } else {
            a >>= -t;                                /* SXM fill flagged */
        }
        *(volatile int *)0xE += -1;                  /* addm #-1,*(0xe) */
        sub_7967();                                  /* call 0x7967 */
        *(*ar2_io)++ = *(*ar4_io)++;                 /* mvdd *ar4+,*ar2+ */
        *(*ar2_io)++ = *(*ar4_io)--;                 /* mvdd *ar4-,*ar2+ */
        *ar3_io -= 32;                               /* mar (banzd delay, every pass) */
    } while (ar7-- != 0);                            /* banzd 0x771a,*ar7- */
}
