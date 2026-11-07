/* ROM6 0x32B4 SUB_3273B -- 58w nibble steering into ROUTINE_423B.
 * Verified encoding: src/rom6/kernel/32b4_sub_3273b.asm (recombine MATCH).
 * ORIGIN 0x32B4
 * EXPECT: 7714 263B 4911 F230 00F0 6884 FF0F 1A84 8084 61F8 3EC8 0010 F820 32D3 F030 00F0 8811 F010 0050 F845 32CE 4811 F010 0030 F844 32D3 E880 6884 FF0F 1A84 8084 F330 000F 10F8 051F F030 FFF0 F2A0 80F8 051F 6184 0060 F020 347F 11F8 0537 F330 0008 F84C 32EB F020 0DE9 FF30 F020 0F45 F074 423B FC00
 *
 * Intent: AR1-entry nibble switch. AR4 = 0x263B (stm). A = *AR1-entry & 240
 * (and #240,b,a: B preserved); cell 0x263B = (cell & -241) | A (andm/or/stl).
 * Cell 0x3EC8 bit 4 clear detours to the 0x32D3 merge (bc ntc; all three bc
 * targets 32CE/32D3/32EB rejoin in-span). Else AR1-entry = A & 240 (stlm);
 * A -= 80, equal (A == 80) runs the 0x32CE set; else A = AR1-entry - 48,
 * nonzero rejoins 0x32D3. The 0x32CE set ORs 128 into cell 0x263B. Merge at
 * 0x32D3: B = B & 15; cell 0x51F = (cell & -16) | B (or b,a). TC = cell
 * 0x263B bits 0x60 any-set (bitf; later ld/ld/and preserve TC per
 * ti-c54x op_logical.c C/TC-preserve, so the xc below reads this TC).
 * B = cell 0x537 & 8; nonzero skips the select and calls ROUTINE_423B with
 * A = 13439 (bc bneq to the call; Z from the and). Else A = TC ? 3909 : 3561
 * (xc 2,tc over ld #3561,a / ld #3909,a) and calls ROUTINE_423B (forward
 * extern frag_423B, A-only contract: entry B recomputed inside). Returns.
 * Bound 32B4-32ED (exit FC00@32ED).
 */
extern void frag_423B(int a_live);

void sub_3273B(int *par1)
{
    volatile int *ar4 = (volatile int *)0x263B;
    long b = (long)*par1;                      /* ldm ar1,b */
    long a = b & 240L;                         /* and #240,b,a (B kept) */

    *ar4 = (*ar4 & -241) | (int)a;             /* andm/or/stl *ar4 */
    if (*(volatile int *)0x3EC8 & 16) {        /* bitf; bc 0x32d3,ntc */
        a &= 240L;                             /* and #240,a */
        *par1 = (int)a;                        /* stlm a,ar1 */
        if (a - 80L == 0 || a - 48L == 0) {    /* sub #80 / sub #48 merge */
            *ar4 = (*ar4 & -241) | 128;        /* 0x32ce: or 128 in */
        }
    }
    /* 0x32d3 merge */
    b &= 15L;                                  /* and #15,b */
    a = (long)*(volatile int *)0x51F;          /* ld *(0x51f),a */
    a = (a & -16L) | b;                        /* and #-16,a; or b,a */
    *(volatile int *)0x51F = (int)a;           /* stl a,*(0x51f) */
    {
        int tc = (*ar4 & 96) != 0;             /* bitf *ar4,#96 (TC) */
        b = (long)*(volatile int *)0x537;      /* ld *(0x537),b */
        b &= 8L;                               /* and #8,b */
        if (b != 0) {                          /* bc 0x32eb,bneq */
            frag_423B(13439);                  /* call 0x423b, A = 13439 */
            return;
        }
        frag_423B(tc ? 3909 : 3561);           /* xc 2,tc select; call */
    }
}
