/* ROM6 0x3266 FRAG_3266 -- 1w.
 * Codegen: cl500 -v548 -O2 byte-identical (build/codegen.json MATCH); .asm retired.
 * ORIGIN 0x3266
 * EXPECT: FC00
 *
 * Intent: Shared RET pad. Branch-target join from WORKER_3199 interior.
 */
void frag_3266(void)
{
    /* ret: no-op join pad */
}
