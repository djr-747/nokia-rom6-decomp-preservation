/* ROM6 0x5362 DISPATCH_SLED_A -- 43w (span 5362-538C, two entries).
 * Verified encoding: src/rom6/rf/5362_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x5362
 * EXPECT: F7BB 74F8 0008 0002 69F8 0008 0080 F495 75F8 0008 0002 F6BB 68F8 0552 FFE3 F074 06E8 E8F0 18F8 2547 60F8 0008 00C0 E803 18F8 2547 F461 FD20 E804 E9F0 19F8 2510 60F8 000B 00C0 F830 538A 76F8 0573 A249 F000 538D F4E2
 *
 * Intent: Branch-entered dispatch sled fragment (5282-family; the
 * 5371 mid-span entry is the call 0x6e8 word -- 5336/5355 tail-call
 * it as frag_5371 per the sled convention: one file, N entry
 * functions, one EXPECT). Head entry frag_5362: INTM = 1 (ssbx,
 * hardware). A = port 2 (portr 2,*(0x8); extern int, AL-alias cell
 * noted). Cell 0x8 |= 128 (orm). Settle nop. Port 2 = cell 0x8
 * (portw; volatile cell read). INTM = 0 (rsbx). Cell 0x552 &= ~29
 * (andm). Falls into the 5371 tail. Tail entry frag_5371 (shared
 * static tail_5371): runs dark SUB_06E8 (no symbol, opaque). A =
 * 240 & *(0x2547) (ld/and). TC = (*(0x8) == 192) (cmpm, 3691
 * precedent). A = 3 & *(0x2547); A <<= 1 (sftl, left exact). TC
 * clear reloads A = 4 (xc 1,ntc; TC preserved through ld/and/
 * sftl). B = 240 & *(0x2510) (ld/and). TC = (*(cell 0xB) == 192)
 * (cmpm on the reada-mailbox cell). TC set skips the 0x573 store
 * (bc 0x538a,tc to L538A). Else *(0x573) = -23991 (st -- the bias
 * the AFAB family adds back). A += 21389 (add #21389; the
 * immediate equals the next ROM address 0x538D, noted; 40-bit wrap
 * flagged). Bacc via A (dark computed target; terminal-branch
 * dark-sink per 5b26). No entry live-ins on either entry (A/B
 * recomputed, ARs untouched); void.
 */
extern int port_read_2(void);                        /* port 2 (2875 precedent) */
extern void port_write_2(int v);                     /* port 2 */
extern void sub_06E8(void);                          /* dark, no symbol */
extern void dark_5362_target(int addr);              /* bacc a (dark computed) */

static void tail_5371(void)
{
    long a;
    long b;
    int tc;
    sub_06E8();                                      /* call 0x6e8 */
    a = 240L & (long)*(volatile int *)0x2547;        /* ld #240,a; and *(0x2547),a */
    tc = (*(volatile int *)0x8 == 192);              /* cmpm *(0x8),#192 */
    a = 3L & (long)*(volatile int *)0x2547;          /* ld #3,a; and */
    a <<= 1;                                         /* sfta a,1 */
    if (!tc)                                         /* xc 1,ntc */
        a = 4;                                       /* ld #4,a */
    b = 240L & (long)*(volatile int *)0x2510;        /* ld #240,b; and */
    (void)b;
    tc = (*(volatile int *)0xB == 192);              /* cmpm *(0xb),#192 */
    if (!tc)                                         /* bc 0x538a,tc fall */
        *(volatile int *)0x573 = -23991;             /* st #-23991,*(0x573) */
    a += 21389L;                                     /* add #21389,a */
    dark_5362_target((int)(a & 0xFFFF));             /* bacc a */
}

void frag_5362(void)
{
    long a;
    /* ssbx st1,intm (hardware, no C form) */
    a = (long)port_read_2();                         /* portr 2,*(0x8) (AL-alias noted) */
    (void)a;
    *(volatile int *)0x8 |= 128;                     /* orm #128,*(0x8) */
    /* nop (settle) */
    port_write_2(*(volatile int *)0x8);              /* portw *(0x8),2 */
    /* rsbx st1,intm (hardware, no C form) */
    *(volatile int *)0x552 &= -29;                   /* andm #-29,*(0x552) */
    tail_5371();                                     /* fall into 5371 */
}

void frag_5371(void)
{
    tail_5371();                                     /* mid-span branch entry */
}
