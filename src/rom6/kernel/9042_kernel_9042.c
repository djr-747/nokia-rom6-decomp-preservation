/* ROM6 0x9042 9042_KERNEL_9042 -- 47w (Pool).
 * Verified encoding: src/rom6/kernel/9042_kernel_9042.asm (recombine MATCH).
 * ORIGIN 0x9042
 * EXPECT: F074 060C F7B7 F072 906E 4497 4187 8392 3D97 8382 308A 5A85 5F95 8E94 8F93 5E85 5B95 8E94 8F93 5A85 5F95 8E94 8F93 5E85 5B95 8E94 8F93 3082 5A85 5F95 8E94 8F93 5E85 5B95 8E94 8F93 5A85 5F95 8E94 8F93 5E85 5BD5 8EDC 8FDB 8D96 F6B7 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ssbx/rsbx st1,c16 have no C form (hardware state)
 * (see src/rom6/kernel/9042_kernel_9042.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
