/* ROM6 0x7F54 FRAG_7F54 -- 1w.
 * Codegen: cl500 -v548 -O2 byte-identical (build/codegen.json MATCH); .asm retired.
 * ORIGIN 0x7F54
 * EXPECT: FC00
 *
 * Intent: Shared RET pad. Two branch entries from SUB_7F75 interior.
 */
void frag_7F54(void)
{
    /* ret: no-op join pad */
}
