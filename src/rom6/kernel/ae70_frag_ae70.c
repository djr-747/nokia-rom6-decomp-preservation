/* ROM6 0xAE70 FRAG_AE70 -- 1w.
 * Codegen: cl500 -v548 -O2 byte-identical (build/codegen.json MATCH); .asm retired.
 * ORIGIN 0xAE70
 * EXPECT: FC00
 *
 * Intent: RET stub. TRACE histogram shows AE70 hits (x10682); HYPOTHESIS.
 */
void frag_AE70(void)
{
    /* ret: no-op stub */
}
