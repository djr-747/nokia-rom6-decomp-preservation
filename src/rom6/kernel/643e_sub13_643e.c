/* ROM6 0x643E SUB13_643E -- 13w.
 * Verified encoding: src/rom6/kernel/643e_sub13_643e.asm (recombine MATCH).
 * ORIGIN 0x643E
 * EXPECT: 60F8 053C 0004 FC20 76F8 2615 0000 70F8 2617 2652 F074 697F FC00
 *
 * Intent: Measure gate plus save. When cell 0x53C reads 4 (cmpm sets TC on equal per ti-c54x op_cmpm; rc ntc skips the next op only when unequal), clears cell 0x2615; always copies cell 0x2652 to 0x2617 (mvdk), runs the 0x697F DARAM save/restore, returns.
 */
extern void daram_save_restore(void);

void sub13_643E(void)
{
    if (*(volatile int *)0x53C == 4)             /* cmpm, rc ntc */
        *(volatile int *)0x2615 = 0;         /* st #0 */
    *(volatile int *)0x2617 =
        *(volatile int *)0x2652;               /* mvkd */
    daram_save_restore();                        /* call 0x697f */
    /* ret */
}
