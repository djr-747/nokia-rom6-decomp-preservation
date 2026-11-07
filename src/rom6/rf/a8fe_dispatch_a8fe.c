/* ROM6 0xA8FE DISPATCH_A8FE -- 30w.
 * Verified encoding: src/rom6/rf/a8fe_dispatch_a8fe.asm (recombine MATCH).
 * ORIGIN 0xA8FE
 * EXPECT: F074 0666 61F8 051C 0040 F830 A91B F274 BBEF 7712 3196 F274 9FCF 7716 288C F074 A12B F274 9F42 771A 009F F274 06A2 7712 3196 F274 BADB 7712 3196 FC00
 *
 * Intent: Long call chain with early return. Runs 0x666; bit 6 of cell 0x51C set returns immediately (bc 0xa91b,tc: target is the lone ret FC00 at 0xA91B, cited, no .asm span so no C file). Else five calld calls with presets (0xBBEF with AR2 = 12694, 0x9FCF with AR6 = 10380, 0xA12B plain, 0x9F42 with BRC = 159, 0x6A2 with AR2 = 12694, 0xBADB with AR2 = 12694; each delay-slot preset executes first); return.
 */
extern void sub_0666(void);
extern void sub_BBEF(void);
extern void sub_9FCF(void);
extern void sub_A12B(void);
extern void sub_9F42(void);
extern void sub_06A2(void);
extern void sub_BADB(void);

static int *G_AR2;
static int *G_AR6;
static int G_BRC;

void dispatch_A8FE_A8FE(void)
{
    sub_0666();                                  /* call 0x666 */
    if ((*(volatile int *)0x51C & 64) != 0) {    /* bitf, bc tc */
        return;                                  /* A91B lone ret */
    }
    G_AR2 = (int *)12694;                        /* calld delay slot */
    sub_BBEF();                                  /* calld 0xbbef */
    G_AR6 = (int *)10380;                        /* calld delay slot */
    sub_9FCF();                                  /* calld 0x9fcf */
    sub_A12B();                                  /* call 0xa12b */
    G_BRC = 159;                                 /* calld delay slot */
    sub_9F42();                                  /* calld 0x9f42 */
    G_AR2 = (int *)12694;                        /* calld delay slot */
    sub_06A2();                                  /* calld 0x6a2 */
    G_AR2 = (int *)12694;                        /* calld delay slot */
    sub_BADB();                                  /* calld 0xbadb */
    /* ret */
}
