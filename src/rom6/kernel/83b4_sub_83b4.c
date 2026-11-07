/* ROM6 0x83B4 SUB_83B4 -- 26w.
 * Verified encoding: src/rom6/kernel/83b4_sub_83b4.asm (recombine MATCH).
 * ORIGIN 0x83B4
 * EXPECT: 4A17 7716 B194 F274 7F75 770E FFFF E800 8A08 F844 83C6 6D92 F074 7FC0 F274 82FF 7716 DD33 F274 7FC6 7712 2A84 69F8 2A87 0400 FC00
 *
 * Intent: Preset call sandwich with in-span skip. Saves AR7 (pshm); AR6 = -20076; T = -1 in the calld delay slot (always executes); calls 0x7F75; A = 0 then AL = popped value = saved AR7 (popm al: the pushed AR7 itself, modeled as live-in); nonzero AL jumps forward into the span at the second calld (bc 0x83c6,aneq skips mar plus the 0x7FC0 call, in-span per bound 83B4-83CD). Else AR2++ (mar, live-in pointer), call 0x7FC0, AR6 = -8909 in the next delay slot, call 0x82FF. Both paths: AR2 = 10884 (delay slot), call 0x7FC6 (live AR2 threaded), set bit 10 of cell 0x2A87 (orm #1024), return.
 */
extern void sub_7F75(void); /* joins 7f75_sub_7f75; see docs/evidence/extern-triage.md */
extern void sub_7FC0(void); /* joins 7fb4_sub32_7f95 interior @+0xB; see docs/evidence/extern-triage.md */
extern void sub_82FF(void); /* joins 82fe_leaf43_82d4 interior @+0x1; see docs/evidence/extern-triage.md */
extern void sub_7FC6(int *par2);

static int *G_AR6;
static int G_T;
static int *G_AR2;

void sub_83B4(int ar7_live, int **ppar2)
{
    int a;
    /* pshm ar7 (hardware state, no C form) */
    G_AR6 = (int *)-20076;                       /* stm #-20076,ar6 */
    G_T = -1;                                    /* calld delay slot */
    sub_7F75();                                  /* calld 0x7f75 */
    a = ar7_live;                                /* ld #0,a; popm al */
    if (a != 0)                                  /* bc 0x83c6,aneq */
        goto L_CALLD6;
    (*ppar2)++;                                 /* mar *ar2+ */
    sub_7FC0();                                  /* call 0x7fc0 */
    G_AR6 = (int *)-8909;                        /* calld delay slot */
    sub_82FF();                                  /* calld 0x82ff */
L_CALLD6:
    G_AR2 = (int *)10884;                        /* calld delay slot */
    sub_7FC6(*ppar2);                            /* calld 0x7fc6 */
    *(volatile int *)0x2A87 |= 1024;         /* orm #1024 */
    /* ret */
}
