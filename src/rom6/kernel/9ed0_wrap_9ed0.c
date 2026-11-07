/* ROM6 0x9ED0 9ED0_WRAP_9ED0 -- 58w (Pool).
 * Verified encoding: src/rom6/kernel/9ed0_wrap_9ed0.asm (recombine MATCH).
 * ORIGIN 0x9ED0
 * EXPECT: F074 06C0 61F8 085D 0020 F820 9F0A 7710 0001 7719 00C8 7212 057D 7713 0926 6DD2 E99F 61F8 0860 0002 F820 9EE9 E94F F073 9EEF 61F8 0860 0090 F820 9EEF E910 47F8 000B E59C 61F8 0861 0001 7712 086F 7682 0002 FF20 69F8 0861 0002 68F8 0861 FFFE 6BF8 057C 0001 69F8 0029 0008 68F8 0029 FFF7 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/9ed0_wrap_9ed0.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
