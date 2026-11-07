/* ROM6 0x4557 FRAG_4557 -- 16w.
 * Verified encoding: src/rom6/kernel/4557_frag_4557.asm (recombine MATCH).
 * ORIGIN 0x4557
 * EXPECT: 456A 456A 455C 455C 4578 4913 7717 052A EC02 7C97 4567 81F8 052B F074 052A FC00
 *
 * Intent: Dead-load program broadcast. Five single-word shifted loads (cells 0x6A/0x5C/0x78 << 16 into B) all overwritten by B = AR3 (ldm, live-in as value; the loads have no side effects, kept in bytes, noted dead); AR7 = 1322; 3 copies (rpt #2) of program word 0x4567 (mvpd absolute: fixed word broadcast, no auto-increment evidenced, flagged like FRAG_4444); cell 0x52B = B; call 0x52A; return.
 */
extern int prom_read_word(int prog_addr);
extern void sub_052A(void);

void frag_4557(int *par3)
{
    int i;
    int b = (int)par3;                           /* 5 dead ld; ldm ar3,b */
    int *ar7 = (int *)1322;                      /* stm #1322,ar7 */
    for (i = 0; i < 3; i++)                       /* rpt #2 */
        *ar7++ = prom_read_word(0x4567);         /* mvpd 0x4567,*ar7+ */
    *(volatile int *)0x52B = b;              /* stl b */
    sub_052A();                                  /* call 0x52a */
    /* ret */
}
