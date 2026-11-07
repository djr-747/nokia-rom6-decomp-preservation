/* ROM6 0x38C9 ROUTINE_38C9 -- 45w scaled add/or with stale-Z gate.
 * Verified encoding: src/rom6/kernel/38c9_routine_38c9.asm (recombine MATCH).
 * ORIGIN 0x38C9
 * EXPECT: 61F8 3EC8 0080 4913 F830 38D6 61F8 3EC8 0020 F495 F495 FD30 F461 61F8 051F 0080 F820 38DE F84D 38DE F461 61F8 3EC8 0020 F010 0026 F57A 81F8 0060 F3E6 0AF8 000B 11F8 0060 F767 F1A0 F300 0026 F820 38F6 69F8 000C 4400 F640 FC00
 *
 * Intent: B = *AR3-entry zero-extended (ldm ar3,b; LDM zero-extends per
 * ti-c54x op_ldm_smem_direct.c). Bit 7 of cell 0x3EC8 set skips the shift
 * (bc tc to 0x38D6). Else bit 5 set doubles A-live-in (xc 1,tc over
 * sfta a,1; nop settles). At 0x38D6: bit 7 of cell 0x51F clear rejoins
 * 0x38DE (bc ntc); set falls to a beq on the ENTRY Z flag -- no in-span op
 * writes Z (ldm/sfta/bitf/nop/xc all Z-preserving: sfta/ldm/load deltas
 * carry no Z write, PRESERVE = 0 per op_effect.h; bitf is TC-only), so the
 * caller Z rides in as z_live and set rejoins 0x38DE. Clear doubles A again
 * (sfta a,1). At 0x38DE: TC4 = bit 5 of cell 0x3EC8 (bitf); A -= 38 (sub,
 * TC-preserving per op_sub_lk.c); B = A >> 6 (sfta a,-6,b, arithmetic);
 * cell 0x60 = B low (stl); B <<= 6 (sftl b,6, TC-preserving per op_shift.c);
 * A -= cell(DP 0x0B) << 16 (subs, TC-preserving per op_subs_smem.c); B =
 * cell 0x60 sign-extended (ld); B <<= 7 (sfta); B |= A (or, TC-preserving
 * per op_logical.c); B += 38 (add, TC-preserving per op_add_lk.c). TC4
 * clear tail-enters FRAG_38F6 with B (bc ntc; bound C frag_38F6, A = B-out,
 * 16-bit narrowing noted). Else cell 0x0C |= 17408 (orm 0x4400); A = B and
 * returns. A, AR3, entry-Z live in; int out. Bound 38C9-38F5 (ret FC00).
 */
extern int frag_38F6(int b_in);

int routine_38C9(int a_live, int *par3, int z_live)
{
    long a = (long)a_live;
    long b = (long)(unsigned int)(unsigned short)*par3; /* ldm ar3,b */

    if ((*(volatile int *)0x3EC8 & 128) == 0) {        /* bc 0x38d6,tc */
        if (*(volatile int *)0x3EC8 & 32)              /* xc 1,tc */
            a <<= 1;                                   /* sfta a,1 */
    }
    /* 0x38d6: bitf *(0x51f),#128; clear rejoins 0x38de */
    if (*(volatile int *)0x51F & 128) {                /* bc 0x38de,ntc */
        if (!z_live)                                   /* bc 0x38de,beq */
            a <<= 1;                                   /* sfta a,1 */
    }
    /* 0x38de merge */
    {
        int tc4 = (*(volatile int *)0x3EC8 & 32) != 0; /* bitf (TC4) */
        a -= 38L;                                      /* sub #38,a */
        b = a >> 6;                                    /* sfta a,-6,b */
        *(volatile int *)0x60 = (int)b;                 /* stl b,*(0x60) */
        b <<= 6;                                       /* sftl b,6 */
        a -= (long)*(volatile int *)0xB << 16;          /* subs *(0xb),a */
        b = (long)*(volatile int *)0x60;               /* ld *(0x60),b */
        b <<= 7;                                       /* sfta b,7 */
        b |= a;                                        /* or a,b */
        b += 38L;                                      /* add #38,b */
        if (!tc4)                                      /* bc 0x38f6,ntc */
            return frag_38F6((int)b);
    }
    *(volatile int *)0xC |= 17408;                      /* orm #17408,*(0xc) */
    return (int)b;                                     /* ld b,a; ret */
}
