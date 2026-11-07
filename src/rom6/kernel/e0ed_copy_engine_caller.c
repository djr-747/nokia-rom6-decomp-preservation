/* ROM6 0xE0ED E0ED_COPY_ENGINE_CALLER -- 87w (Pool).
 * Verified encoding: src/rom6/kernel/e0ed_copy_engine_caller.asm (recombine MATCH).
 * ORIGIN 0xE0ED
 * EXPECT: 4812 0864 8812 771A 0013 4A12 4A13 4A14 F274 E532 7714 1128 7712 1128 7713 1150 ED1E 4492 EC26 C889 C841 F062 0400 F484 EC26 388A 3882 FA47 E111 ED00 E800 E732 F020 FFFE 6DEA FFD9 806B E721 7716 1100 1065 0864 8817 7710 FFD9 8A14 8A13 8A15 7666 0001 6D8D 6DEB 0027 2692 EC24 3892 F274 E54B 3892 3892 E712 826C 406C 6F6D 0C9F A48A EC25 B08A B00E 826E 406E 6F6F 0C9F 306E 216C 206D 3566 306F 206C 3566 4817 F74F F741 8396 116B FD45 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e0ed_copy_engine_caller.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
