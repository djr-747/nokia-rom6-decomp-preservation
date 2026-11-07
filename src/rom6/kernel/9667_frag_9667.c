/* ROM6 0x9667 FRAG_9667 -- 27w.
 * Verified encoding: src/rom6/kernel/9667_frag_9667.asm (recombine MATCH).
 * ORIGIN 0x9667
 * EXPECT: F495 7582 0036 80F8 20FC E800 68F8 20FF FFBF 61F8 20FF 0080 FA20 283D 80F8 20FB 74F8 000B 000C 1BF8 3ECA F495 75F8 000B 000C F073 283D
 *
 * Intent: Port-12 status fork. Port 54 = *AR2 (portw, extern-op
 * placeholder per the 2867/2875 precedent); cell0x20FC = A-low
 * (entry A live); A = 0; cell0x20FF &= -65; TC = (cell & 128) != 0;
 * the bcd delay cell0x20FB = 0 always runs (A = 0); TC clear
 * tail-enters dark 0x283D (bcd ntc, grounded per ti-c54x op_bcd:
 * taken = DELAYED_PC_WRITE; void per the 2867 precedent). Else
 * cell0xB = port 12 (portr writes Smem only -- A is NOT reloaded,
 * the 2867 A-load came from the cell-8 AL alias, not the op;
 * cell 0xB is the reada pointer, flagged); B |= cell0x3ECA; port 12
 * = cell0xB; tail-branch dark 0x283D (A = 0, B computed; liveness
 * through the dark call unbound, flagged). Bound 9667-9681.
 */
extern void port_write_54(int v);
extern int port_read_12(void);
extern void port_write_12(int v);
extern void frag_283D(void);

void frag_9667(long a_live, int *ar2, long b_live)
{
    long a = a_live;
    long b = b_live;
    int tc;
    int pv;
    /* nop */
    port_write_54(*ar2);                             /* portw *ar2,54 */
    *(volatile int *)0x20FC = (int)(a & 0xFFFF);     /* stl a,*(0x20fc) */
    a = 0;                                           /* ld #0,a */
    *(volatile int *)0x20FF &= -65;                  /* andm #-65,*(0x20ff) */
    tc = (*(volatile int *)0x20FF & 128) != 0;       /* bitf *(0x20ff),#128 */
    *(volatile int *)0x20FB = 0;                     /* bcd delay: stl (always runs) */
    if (!tc) {                                       /* bcd 0x283d,ntc */
        frag_283D();
        return;
    }
    pv = port_read_12();                             /* portr 12,*(0xb) */
    *(volatile int *)0xB = pv;
    b |= (long)*(volatile int *)0x3ECA;              /* or *(0x3eca),b */
    /* nop */
    port_write_12(*(volatile int *)0xB);             /* portw *(0xb),12 */
    /* A = 0, B computed: live into dark 283D (unbound, flagged) */
    frag_283D();                                     /* b 0x283d */
}
