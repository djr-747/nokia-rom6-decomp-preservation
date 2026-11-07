/* ROM6 0x56BD TABLE_56BD -- 33w.
 * Verified encoding: src/rom6/tables/56bd_table_56bd.asm (recombine MATCH).
 * ORIGIN 0x56BD
 * EXPECT: 2A39 2E3D 5D06 610A 202F 2433 2837 2C3B 5362 5700 5B04 5F08 06FF 0CFF 10FF 16FF 1AFF 20FF 24FF 2AFF 2EFF 1625 1A29 202F 2400 000F 0413 0817 0C1B 101F 1423 1827 1C2B
 *
 * Intent: Read-only data table (33 words, pure .word data, no code).
 */
static const unsigned int table_56bd[33] = {
    0x2A39, 0x2E3D, 0x5D06, 0x610A, 0x202F, 0x2433, 0x2837, 0x2C3B,
    0x5362, 0x5700, 0x5B04, 0x5F08, 0x06FF, 0x0CFF, 0x10FF, 0x16FF,
    0x1AFF, 0x20FF, 0x24FF, 0x2AFF, 0x2EFF, 0x1625, 0x1A29, 0x202F,
    0x2400, 0x000F, 0x0413, 0x0817, 0x0C1B, 0x101F, 0x1423, 0x1827,
    0x1C2B
};
