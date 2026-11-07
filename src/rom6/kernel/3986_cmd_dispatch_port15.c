/* ROM6 0x3986 CMD_DISPATCH_PORT15 -- 2w STUB.
 * Verified encoding: src/rom6/kernel/3986_cmd_dispatch_port15.asm (recombine MATCH).
 * ORIGIN 0x3986
 * EXPECT: F074 062E
 *
 * Intent: Entry-call stub (the .asm captures only the head call; the span body from 0x3988 through RET at 0x399D per the header evidence has no .asm and stays dark). Head-calls dark SUB_062E. Defines SUB_3986 for the A482 caller.
 */
extern void sub_062E(void);

void sub_3986(void)
{
    sub_062E();                                    /* call 0x62e */
}
