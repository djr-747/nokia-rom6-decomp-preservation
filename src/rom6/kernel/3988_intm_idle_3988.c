/* ROM6 0x3988 3988_INTM_IDLE_3988 -- 22w (Pool).
 * Verified encoding: src/rom6/kernel/3988_intm_idle_3988.asm (recombine MATCH).
 * ORIGIN 0x3988
 * EXPECT: F7BB 68F8 263A FFFD 61F8 2639 0200 F830 3997 F495 75F8 0008 000F EC06 F495 F6BB F4E1 F7BB 61F8 263A 0002 F820
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ssbx/rsbx st1,intm + idle have no C form (hardware state). Bound 3988-399D (post-call head after 3986 call
 * (see src/rom6/kernel/3988_intm_idle_3988.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
