/* ROM6 0x454F SUB_454F -- 8w.
 * Verified encoding: src/rom6/kernel/454f_sub_454f.asm (recombine MATCH).
 * ORIGIN 0x454F
 * EXPECT: F000 4557 7EF8 000B F5E3 6C8E 4551 FC00
 *
 * Intent: Computed-call dispatch loop. Biases A by 17751, then repeats: reload A from program memory at data cell 0xB (reada), call the address in B (cala b, B live-in), until AR6 counts down (banz 0x4551, test-then-decrement per ti-c54x op_banz ground truth: while (ar6-- != 0)). A completed pass returns.
 */
typedef void (*dispatch_fn_t)(void);
extern int prom_read_word(int data_addr);      /* reada: program-memory read */

void sub_454F(int a_in, int b_in, int ar6_in)
{
    int a = a_in + 17751;                        /* add #17751,a */
    int ar6 = ar6_in;
    do {
        a = prom_read_word(*(volatile int *)0xB); /* reada *(0xb) */
        ((dispatch_fn_t)b_in)();                 /* cala b */
    } while (ar6-- != 0);                        /* banz 0x4551,*ar6- */
    (void)a;
    /* ret */
}
