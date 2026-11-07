/* ROM6 0x43EA 43EA_PORT35_DISPATCH -- 73w (Pool).
 * Verified encoding: src/rom6/rf/43ea_port35_dispatch.asm (recombine MATCH).
 * ORIGIN 0x43EA
 * EXPECT: F074 0594 7714 2F00 1084 F030 00FF 71D2 0013 6FD2 0D58 F310 0001 891A 8916 F495 F072 43FD 11D2 8194 F074 2E2F 7714 2F00 F000 4433 7EF8 000B F5E3 6C8E 4404 F010 4435 FC44 60F8 0013 0023 FC20 E900 771A 001F F072 4419 F495 75F8 000B 0023 F495 6D8C 771A 001F 60F8 08F1 00A2 F820 4425 771A 001E 1084 F072 442A F495 758C 0023 F495 F820 4432 F495 75F8 0008 0023 F495 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS via 4433 cala-b table words 4439/4444/4453/4444/446D/4474)
 * (see src/rom6/rf/43ea_port35_dispatch.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
