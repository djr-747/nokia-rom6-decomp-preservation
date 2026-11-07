/* ROM6 0x7F1C 7F1C_DEAD_LANES_7F1C -- 57w (Pool).
 * Verified encoding: src/rom6/kernel/7f1c_dead_lanes_7f1c.asm (recombine MATCH).
 * ORIGIN 0x7F1C
 * EXPECT: 770E 0000 F273 7F75 7716 B163 770E FFFF F273 7F75 7716 B194 770E FFFE F273 7F75 7716 B18C 770E FFFD F273 7F75 7716 B184 F074 7FC0 770E FFFC F273 7F95 7716 B17C F074 7FC0 770E FFFB F273 7F95 7716 B174 F074 7FC0 770E FFFA F273 7F95 7716 B16C F074 7FC0 770E FFF9 F273 7F95 7716 B164 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * dead lane, annotated).
 * (see src/rom6/kernel/7f1c_dead_lanes_7f1c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
