/* ROM6 0x6458 6458_MPYA_LADDER_6458 -- 69w (Pool).
 * Verified encoding: src/rom6/kernel/6458_mpya_ladder_6458.asm (recombine MATCH).
 * ORIGIN 0x6458
 * EXPECT: F843 6462 8093 6083 CFFF 6B83 0001 FF30 7683 0000 7711 2FD9 128A F030 0003 8809 770E 0033 F58C 0186 0182 F210 00CC 7710 0917 FD43 F640 8091 1080 0086 F110 0066 7710 250F FD4B F540 8181 12F8 0916 F030 0007 8809 770E 0033 F58C 01F8 0915 0186 F210 0198 7711 2FEC FD43 F640 8081 1080 F130 00F0 60F8 0008 0050 F820 64A0 F074 6871 F84C 676A F074 688D
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: stlm a,ah (8809, wave-12). STLM_SMEM_DIRECT has a catalog row (0x8800) and a leaf, but the leaf punts MMR-register routing downstream ("MMR-register routing is downstream") and no in-tree precedent r
 * (see src/rom6/kernel/6458_mpya_ladder_6458.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
