/* ROM6 0x4ADF FRAG_4ADF -- 1w.
 * Codegen: cl500 -v548 -O2 byte-identical (build/codegen.json MATCH); .asm retired.
 * ORIGIN 0x4ADF
 * EXPECT: FC00
 *
 * Intent: RET end pad. Seven inbound branch joins, zero callers.
 */
void frag_4ADF(void)
{
    /* ret: no-op region-end pad */
}
