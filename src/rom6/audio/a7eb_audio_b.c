/* ROM6 0xA7EB AUDIO_B_A7EB -- 27w.
 * Verified encoding: src/rom6/audio/a7eb_audio_b.asm (recombine MATCH).
 * ORIGIN 0xA7EB
 * EXPECT: F074 0660 61F8 2628 0100 7712 260E FB30 ABD2 7713 022B 61F8 2628 4000 FC30 61F8 058F 000F F830 A803 61F8 051D 0200 FC30 F074 9E85 FC00
 *
 * Intent: Audio worker B. Runs 0x660; bit 8 of cell 0x2628 set calls 0xABD2 (ccd tc, AR2 = 9742 then AR3 = 555 presets in/after the delay slot, always execute); bit 14 set skips ahead (rc tc); bit 0 of cell 0x58F set jumps to the A803 stub (bc 0xa803,tc: A803 = call 0x9E85 plus ret, inlined here with byte citation); bit 9 of cell 0x51D set skips the final call (rc tc); else call 0x9E85; return. BITF any-bit TC per ti-c54x op_bitf.
 */
extern void sub_0660(void);
extern void sub_ABD2(void);
extern void sub_9E85(void);

static int *G_AR2;
static int *G_AR3;

void audio_B_A7EB(void)
{
    sub_0660();                                  /* call 0x660 */
    G_AR2 = (int *)9742;                         /* stm #9742,ar2 */
    if ((*(volatile int *)0x2628 & 256) != 0) {  /* bitf, ccd tc */
        G_AR3 = (int *)555;                      /* ccd delay slot */
        sub_ABD2();                              /* calld 0xabd2 */
    } else {
        G_AR3 = (int *)555;                      /* delay slot: always */
    }
    if ((*(volatile int *)0x2628 & 16384) != 0)  /* bitf, rc tc */
        return;
    if ((*(volatile int *)0x58F & 15) != 0) {    /* bitf, bc tc */
        sub_9E85();                              /* A803 stub inlined */
        return;
    }
    if ((*(volatile int *)0x51D & 512) != 0)     /* bitf, rc tc */
        return;
    sub_9E85();                                  /* call 0x9e85 */
    /* ret */
}
