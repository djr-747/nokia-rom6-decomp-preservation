/* ROM6 0x8FAE 8FAE_WORKER_8FAE -- 86w (Pool).
 * Verified encoding: src/rom6/kernel/8fae_worker_8fae.asm (recombine MATCH).
 * ORIGIN 0x8FAE
 * EXPECT: F074 0668 4A11 E800 F586 7710 2F0F 4A0B 7715 2F10 7716 2F12 FB81 A50D 7717 2F11 E900 8A0B F761 890E 8A11 E800 7713 3028 FB81 A54E 7712 303A 7713 303A 7712 2F06 FB81 A4F6 7715 2F03 7711 0CCD 7713 2F07 11F8 2F03 FB81 A59C 7712 3028 7716 2F14 10F8 0A44 00F8 0A43 F47E 8386 770E 0000 FF46 7686 0001 7712 2F06 7713 2F03 7710 2F0F 7715 2F1C EC05 708D B3B0 6D95 FB81 A622 7717 2F11 10F8 2F0F FB81 A6E2 11F8 2F10 FB81 A704 770E 0005 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/8fae_worker_8fae.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
