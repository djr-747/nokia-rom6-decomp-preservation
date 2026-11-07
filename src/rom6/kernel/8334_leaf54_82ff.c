/* ROM6 0x8334 SUB56_8335 -- 56w (LEAF54_82FF exit abut + dark-dispatch head).
 * Verified encoding: src/rom6/kernel/8334_leaf54_82ff.asm (recombine MATCH).
 * ORIGIN 0x8334
 * EXPECT: FC00 F074 066E 7712 2A84 7711 2A8B 10F8 2631 00F8 2630 F000 8345 F030 FFFF 7EF8 000B F5E2 834E 836D 838C 83A0 83B4 83CE 83E8 83FF 4917 F84C 835D F274 82D4 7716 DD33 7716 B174 F274 7F95 770E FFF3 F073 8365 F074 7FC0 7716 B174 F274 7F95 770E FFFB F274 7FC6 7712 2A84 69F8 2A87 0200
 *
 * Intent: Head word ret@8334 is the LEAF54_82FF exit abut (not modeled;
 * the leaf body lives ahead of this span). Body entry sub_8335 (1 caller
 * calld @81C2): runs dark SUB_0686 (low-zone mini-kernel, no symbol,
 * opaque), seats AR2 = 10884, AR1 = 10891 (locals, dead after, noted).
 * A = cell 0x2631 + cell 0x2630 - 31931 (dual add + immediate, signed),
 * A &= 0xFFFF (and #-1, 16-bit mask per the AND_IMMEDIATE rule).
 * Cell 0xB = program[A] (reada, oracle program-to-Smem direction per
 * op_reada.h; the 454F committed model reads the reverse direction --
 * correction debt logged in worklog). Control transfers via bacc b with
 * B entry-dark (call 0686 clobbers; never set in-span) to
 * dark_8335_target (28a5 terminal-extern precedent; permanently dark
 * computed branch, no fall-through). Post-bacc tail 8346-836B (7x sth b
 * lanes, ldm ar7, bc 0x835d, calld 82D4/7F95/7FC0/7FC6, b 0x8365,
 * orm #512,*(0x2a87)) is unreachable-in-model and is documented here,
 * not executed: bacc never falls through, and a whole-image scan finds
 * no external xref into 8346-836B. Exit ret@836C owned by
 * 836c_sub56_8335 (which owns the sub56_8335 name). Out cells/A/ARs;
 * B/C/TC dark. EXPECT from the image.
 */
extern void sub_0686(void);               /* dark, no symbol (low-zone) */
extern int prom_read_word(int data_addr); /* reada (454F precedent) */
extern void dark_8335_target(int addr);   /* bacc b (dark computed) */

void sub_8335(long b_in)
{
    long a;
    int *ar1;
    int *ar2;

    /* ret@8334: LEAF54_82FF exit abut, not modeled */
    sub_0686();                                                 /* call 0x66e */
    ar2 = (int *)(long)10884;                                   /* stm #10884,ar2 */
    ar1 = (int *)(long)10891;                                   /* stm #10891,ar1 */
    a = (long)*(volatile int *)0x2631;                          /* ld *(0x2631),a */
    a += (long)*(volatile int *)0x2630;                         /* add *(0x2630),a */
    a += -31931L;                                               /* add #-31931,a */
    a &= 0xFFFFL;                                               /* and #-1,a (16-bit mask) */
    *(volatile int *)0xB = prom_read_word((int)(a & 0xFFFFL));  /* reada *(0xb) */
    dark_8335_target((int)(b_in & 0xFFFFL));                    /* bacc b */
}
