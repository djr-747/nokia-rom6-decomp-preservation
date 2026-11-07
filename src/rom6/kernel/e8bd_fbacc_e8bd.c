/* ROM6 0xE8BD E8BD_FBACC_E8BD -- 10w (Pool).
 * Verified encoding: src/rom6/kernel/e8bd_fbacc_e8bd.asm (recombine MATCH).
 * ORIGIN 0xE8BD
 * EXPECT: 7711 234A F071 009F 8091 80F8 2964 8A0C 8A0B F5E6
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: fbacc b (F5E6) with runtime target has no grounded C form. Post-fbacc head
 * (see src/rom6/kernel/e8bd_fbacc_e8bd.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
