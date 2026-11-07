/* ROM6 0x538D DISPATCH_SLED_A -- 8w.
 * Verified encoding: src/rom6/rf/538d_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x538D
 * EXPECT: F073 5395 F073 53EB F073 5434 F073 544A
 *
 * Intent: Branch sled with four entries. Each 2w slot is an independent entry tail-calling its lane (entered via branch at 2w intervals, zero callers per header): slot 0 to 0x5395, slot 1 to 0x53EB, slot 2 to 0x5434, slot 3 to 0x544A (5395/53EB/544A C-bound with TC threading into 53EB; 5434 has .asm, no C yet, forward extern). One file, four entry functions, one EXPECT over the whole span. 8w per .asm header (Bound 538D-5394; recombine MATCH).
 */
extern void frag_5395(void);
extern void frag_53EB(int tc_live);
extern void frag_5434(void);
extern void frag_544A(void);

void sled_538D_0(void)
{
    frag_5395();                                     /* b 0x5395 */
}
void sled_538D_1(int tc_live)
{
    frag_53EB(tc_live);                              /* b 0x53eb (TC threads) */
}
void sled_538D_2(void)
{
    frag_5434();                                     /* b 0x5434 (unbound C) */
}
void sled_538D_3(void)
{
    frag_544A();                                     /* b 0x544a */
}
