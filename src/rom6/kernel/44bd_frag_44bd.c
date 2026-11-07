/* ROM6 0x44BD FRAG_44BD -- 26w.
 * Verified encoding: src/rom6/kernel/44bd_frag_44bd.asm (recombine MATCH).
 * ORIGIN 0x44BD
 * EXPECT: F074 0594 F074 2E2F 7713 2F00 F028 000A F040 0009 8093 7712 0060 7682 0100 7D82 FF87 7714 0074 7C8B FF87 F274 2C88 7715 0004 FC00
 *
 * Intent: Overlay patch plus readback. Runs 0x594 then the 0x2E2F dispatcher entry; AR3 = 12032; A = (10 << 8) OR 9 stored with post-increment (12032 then AR3 = 12033); AR2 = 96; *AR2 = 256; program word 0xFF87 = 256 (mvdp data-to-program write, extern prom_write_word); AR4 = 116; *AR3-- = program word 0xFF87 (mvpd readback, extern prom_read_word; AR3 back to 12032); calls 0x2C88 with AR5 = 4 in the calld delay slot (executes first); return.
 */
extern void helper_0594(void);
extern void dispatcher_entry_2E2F(void);
extern void prom_write_word(int prog_addr, int v); /* mvdp */
extern int prom_read_word(int prog_addr);          /* mvpd */
extern void sub_2C88(void);

static int *G_AR3;
static int *G_AR2;
static int *G_AR4;
static int *G_AR5;

void frag_44BD(void)
{
    int a;
    helper_0594();                               /* call 0x594 */
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    G_AR3 = (int *)12032;                        /* stm #12032,ar3 */
    a = (10 << 8) | 9;                           /* ld #10,8,a; or #9,a */
    *G_AR3++ = a;                                /* stl a,*ar3+ */
    G_AR2 = (int *)96;                           /* stm #96,ar2 */
    *G_AR2 = 256;                               /* st #256,*ar2 */
    prom_write_word(0xFF87, *G_AR2);             /* mvdp *ar2,0xff87 */
    G_AR4 = (int *)116;                          /* stm #116,ar4 */
    *G_AR3-- = prom_read_word(0xFF87);           /* mvpd 0xff87,*ar3- */
    G_AR5 = (int *)4;                            /* calld delay slot */
    sub_2C88();                                  /* calld 0x2c88 */
    /* ret */
}
