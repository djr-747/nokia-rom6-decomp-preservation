/* ROM6 0x9D9A 9D9A_WRAP_9D9A -- 61w (Pool).
 * Verified encoding: src/rom6/kernel/9d9a_wrap_9d9a.asm (recombine MATCH).
 * ORIGIN 0x9D9A
 * EXPECT: F074 06BE 10F8 085D 771A 009F 60F8 0573 AF57 F820 9DAD F130 0008 F84D 9DBB F030 0004 F073 9DB3 F130 0004 F84D 9DBB F030 0008 F272 9DBA 7712 29C9 4593 FD44 3F82 8392 10F8 085D F130 0003 F030 000C F845 9DD7 61F8 2AEB 0001 68F8 0860 9FFF 61F8 2AEE 0001 FF30 69F8 0860 2000 FF30 69F8 0860 4000 F074 9C99 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/9d9a_wrap_9d9a.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
