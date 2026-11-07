/* ROM6 0x836D SUB_836D -- 31w.
 * Verified encoding: src/rom6/kernel/836d_sub_836d.asm (recombine MATCH).
 * ORIGIN 0x836D
 * EXPECT: 4917 F84C 837C F274 82D4 7716 DCFA 7716 B17C F274 7F95 770E FFF4 F073 8384 F074 7FC0 7716 B17C F274 7F95 770E FFFC F274 7FC6 7712 2A84 69F8 2A87 0200 FC00
 *
 * Intent: AR7-dispatched twin-lane join. B = *AR7-entry (ldm). Nonzero takes
 * the 837C lane: runs dark SUB_7FC0 (forward extern), then dark SUB_7F95
 * (calld, T = -4 delay preset, forward extern), falls into 8384. Zero runs
 * the 8370 lane: dark SUB_82D4 (calld, AR6 = -8966 delay preset, dead,
 * overwritten), AR6 = -20100, dark SUB_7F95 (calld, T = -12 delay preset),
 * branches to 8384 (b). Join at 8384: dark SUB_7FC6 (calld, delay
 * AR2 = 10884 runs first), cell 0x2A87 |= 512 (orm), return. Delay-slot
 * presets are callee-visible pre-branch state (836d precedent); AR7 the only
 * entry read; A dead at return, flagged. Former 15w bound (836D-837B with
 * dark frag_837C/frag_8384 externs) extended wave-12 to the ret @838B; the
 * 837C-838B lane words were owned by the deleted 836c draft (which also
 * duplicated 838C-839F/83A0-83A3). Bound 836D-838B, abuts 838C.
 */
extern void sub_82D4(void);
extern void sub_7F95(void);
extern void sub_7FC0(void);
extern void sub_7FC6(void);

void sub_836D(int *par7)
{
    long b = (long)*par7;                      /* ldm ar7,b */

    if (b != 0) {                              /* bc 0x837c,bneq */
        sub_7FC0();                            /* call 0x7fc0 (837C lane) */
        /* stm #-20100,ar6 (preset rides into 7f95) */
        /* calld 0x7f95; delay stm #-4,t (T preset visible to callee) */
        sub_7F95();
        /* fall into 8384 */
    } else {
        /* calld 0x82d4; delay stm #-8966,ar6 (dead, overwritten below) */
        sub_82D4();
        /* stm #-20100,ar6 */
        /* calld 0x7f95; delay stm #-12,t (T preset visible to callee) */
        sub_7F95();
        /* b 0x8384 */
    }
    /* 8384 join: calld 0x7fc6; delay stm #10884,ar2 (runs first) */
    sub_7FC6();
    *(volatile int *)0x2A87 |= 512;            /* orm #512,*(0x2a87) */
    /* ret */
    (void)b;
}
