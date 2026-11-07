/* ROM6 0x83CE SUB_83CE -- 26w.
 * Verified encoding: src/rom6/kernel/83ce_sub_83ce.asm (recombine MATCH).
 * ORIGIN 0x83CE
 * EXPECT: 4A17 7716 B163 F274 7F75 770E 0000 E800 8A08 F844 83E0 6D92 F074 7FC0 F274 82FF 7716 DCFA F274 7FC6 7712 2A84 69F8 2A87 0400 FC00
 *
 * Intent: Preset call sandwich with in-span skip. Same shape as SUB_83B4 with AR6 presets -20125/-8966 and T preset 0; nonzero popped AL (saved AR7, modeled live-in) jumps forward into the span at the second calld (bc 0x83e0,aneq, in-span per bound 83CE-83E7); else the 0x7FC0 call first. Both paths: AR2 = 10884, call 0x7FC6 (live AR2 threaded), set bit 10 of cell 0x2A87, return.
 */
extern void sub_7F75(void);
extern void sub_7FC0(void);
extern void sub_82FF(void);
extern void sub_7FC6(int *par2);

static int *G_AR6;
static int G_T;
static int *G_AR2;

void sub_83CE(int ar7_live, int **ppar2)
{
    int a;
    /* pshm ar7 (hardware state, no C form) */
    G_AR6 = (int *)-20125;                       /* stm #-20125,ar6 */
    G_T = 0;                                     /* calld delay slot */
    sub_7F75();                                  /* calld 0x7f75 */
    a = ar7_live;                                /* ld #0,a; popm al */
    if (a != 0)                                  /* bc 0x83e0,aneq */
        goto L_CALLD6;
    (*ppar2)++;                                 /* mar *ar2+ */
    sub_7FC0();                                  /* call 0x7fc0 */
    G_AR6 = (int *)-8966;                        /* calld delay slot */
    sub_82FF();                                  /* calld 0x82ff */
L_CALLD6:
    G_AR2 = (int *)10884;                        /* calld delay slot */
    sub_7FC6(*ppar2);                            /* calld 0x7fc6 */
    *(volatile int *)0x2A87 |= 1024;         /* orm #1024 */
    /* ret */
}
