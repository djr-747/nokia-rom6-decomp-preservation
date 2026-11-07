/* ROM6 0xE79D E79D_EXT_CALL_STUB_C -- 82w (Pool).
 * Verified encoding: src/rom6/kernel/e79d_ext_call_stub_c.asm (recombine MATCH).
 * ORIGIN 0xE79D
 * EXPECT: F074 05B0 61F8 051D 0100 F820 E7A7 76F8 050E 0000 76F8 296A 2800 76F8 296C 2800 76F8 296D 2800 76F8 296B 2800 76F8 2969 0000 76F8 2978 0000 76F8 2966 0002 76F8 2967 0000 76F8 2968 0000 76F8 2977 0000 68F8 0537 EC97 76F8 2453 0000 61F8 051D 0100 F820 E7DE 68F8 054F FFDF 68F8 051D FEFF 69F8 2453 0002 76F8 050B 0000 F073 E7EE 7713 051E 61F8 054F 0008 6883 BFFF FF30 6983 4000 68F8 054F FFF7 68F8 051E FFF7 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e79d_ext_call_stub_c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
