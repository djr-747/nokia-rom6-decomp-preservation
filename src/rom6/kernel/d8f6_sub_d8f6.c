/* ROM6 0xD8F6 SUB_D8F6 -- 21w.
 * Verified encoding: src/rom6/kernel/d8f6_sub_d8f6.asm (recombine MATCH).
 * ORIGIN 0xD8F6
 * EXPECT: F074 0684 4A07 7707 0740 7719 0000 76F8 300A 3088 7712 3044 F274 D2E2 7713 09C8 7712 3043 8092 8A07 FC00
 *
 * Intent: Mode-switch call pair. Runs 0x684; saves ST1 (pshm); ST1 = 1856, BK = 0 (hardware mode state, BK comments the circular-buffer size select); cell 0x300A = 12424; AR2 = 12356 feeds 0xD2E2 with AR3 = 2504 in the calld delay slot (executes first); AR2 = 12355 gets A (sub_D2E2 result); ST1 restored (popm, hardware state); return.
 */
extern void sub_0684(void);
extern int sub_D2E2(void);

static int *G_AR2;
static int *G_AR3;

void sub_D8F6(void)
{
    int a;
    sub_0684();                                  /* call 0x684 */
    /* pshm st1; stm #1856,st1; stm #0,bk (mode state, no C form) */
    *(volatile int *)0x300A = 12424;         /* st */
    G_AR2 = (int *)12356;                        /* stm #12356,ar2 */
    G_AR3 = (int *)2504;                         /* calld delay slot */
    a = sub_D2E2();                              /* calld 0xd2e2 */
    G_AR2 = (int *)12355;                        /* stm #12355,ar2 */
    *G_AR2++ = a;                                /* stl a,*ar2+ */
    /* popm st1: ST1 restore (hardware state, no C form) */
    /* ret */
}
