/* ROM6 0xAE6C JUMP_TABLE_4 -- 4w.
 * Verified encoding: src/rom6/tables/ae6c_jump_table_4.asm (recombine MATCH).
 * ORIGIN 0xAE6C
 * EXPECT: AE70 AE71 AE75 AE79
 *
 * Intent: 4-way jump table between RET@AE6B and RET@AE70. Consumer is
 * the 0xAD0D dispatch driver (add #AE6C @ADDA, reada @ADDE, cala b
 * @ADE0). All four entries are routine heads.
 */
static const unsigned int jump_table_4[4] = {
    0xAE70, 0xAE71, 0xAE75, 0xAE79
};
