/* ROM6 0x3D3D ROUTINE_3D3D -- 60w (the .asm header's 62w note miscounts 0x3B+1).
 * Verified encoding: src/rom6/kernel/3d3d_routine_3d3d.asm (recombine MATCH).
 * ORIGIN 0x3D3D
 * EXPECT: F074 05AA 771A 001F F072 3D77 4482 3CF8 0571 61F8 3EB5 0004 F820 3D5B 4A08 4A09 4A0A 44F8 057A 40F8 0578 3184 F300 4000 890E 8A0A 8A09 8A08 F48C F462 3190 F762 3F85 61F8 3EB5 0008 F820 3D69 30F8 0578 44F8 057A F462 F788 F062 03FF F487 4917 60F8 0017 0002 F061 0200 FD4D 828E FD30 8289 FD20 8291 FC00
 *
 * Intent: Tune-math MAC lane with three conditional
 * stores. Runs 0x5AA (dark, extern); BRC = 31; 32 passes
 * (rptb 0x3d77, REA 0x3d77; the ret sits past the loop).
 * Per pass: A = *(AR2) << 16 (ld Smem,16, no step) plus
 * cell 0x571 << 16 (add Smem,16); the two <<16 terms fit
 * long with the running sums assumed small (flagged --
 * full 40-bit needs long long, which cl500 rejects per
 * the 4EBC file); TC = bit 2 of cell 0x3EB5 (bitf);
 * clear skips the save block to the 3D5B join (bc ntc).
 * Save block: A pushed (pshm al/ah/ag; the stack has no
 * C form -- an a_saved local carries it per the 2D5E
 * precedent); A = cell 0x57A << 16 minus cell 0x578 << 16
 * (sub Smem,16); B = *AR4 times A-high (mpya Smem
 * overwrites B per op_mpya_smem and the 4EBC precedent);
 * B += 16384 (add lk); T = B-low (stlm b,t, int local);
 * A popped (popm triple). Then A = T times A-high (mpya
 * a: D = 0 selects A per the dst-leaf opcode note, STORE
 * with no rounding; T and the A-high source ride
 * unchanged); A arith>>= 2 (sfta). 3D5B join: B = *(AR0)
 * times A-high with AR0 post-incremented (mpya *ar0+;
 * circular wrap needs caller-live BK, linear modeled
 * flagged); B arith>>= 2 (sfta); B += *AR5 << 16 (add
 * Smem,16); TC = bit 3 of cell 0x3EB5; clear skips to
 * the 3D69 join (bc ntc), else T = cell 0x578 (ld Smem,T
 * direct: no ti-c54x catalog row, same gap class as the
 * 3306 LD_MOD10 -- binutils decode plus the 423B mvdm-T
 * precedent, flagged); A = cell 0x57A << 16, arith>>= 2;
 * B = B plus T times A-high (maca t,b: S = 1, D = 1,
 * R = 0 from the F788 word per the layout set -- B
 * accumulates, unrounded). 3D69 join: A = 1023 << 16;
 * A = min(A,B), signed full-width per op_compare (the
 * min a destination bit selects A); B = zero-extended
 * AR7 (ldm, oracle zero-extends); TC = (cell 0x17 == 2)
 * (cmpm, oracle: TC = equality); A -= 512 << 16 (sub
 * lk,16, exact); A == 0 skips the AR6 store (xc 1,beq
 * covers the 1-word sth); the cmpm TC selects the AR1
 * store direction (xc 1,tc stores HIGH of A to *(AR1--)
 * else xc 1,ntc stores to *(AR1++); STH stores A[31:16],
 * exact via long). FRCT assumed 0 and OVM small-values
 * throughout (unbound status, flagged per house rule).
 * A/B are pass-local (every path writes before reading);
 * T local; AR2/AR4/AR5/AR7 read-only; AR0/AR6/AR1 step
 * on locals; all dead at return (flagged). Bound
 * 3D3D-3D78.
 */
extern void sub_05AA(void);

void routine_3D3D(int *ar2_in, int *ar4_in, int ar0_live, int *ar5_in, int *ar6_in, int *ar1_in, int ar7_live)
{
    int *ar2 = ar2_in;
    int *ar4 = ar4_in;
    int ar0 = ar0_live;
    int *ar5 = ar5_in;
    int *ar6 = ar6_in;
    int *ar1 = ar1_in;
    long a;
    long b;
    int t;
    int i;
    sub_05AA();                                      /* call 0x5aa */
    /* stm #31,brc */
    for (i = 0; i < 32; i++) {                       /* rptb 0x3d77 */
        a = (long)*ar2 << 16;                        /* ld *ar2,16,a */
        a += (long)*(volatile int *)0x571 << 16;     /* add *(0x571),16,a */
        if ((*(volatile int *)0x3EB5 & 4) != 0) {    /* bitf; bc ntc */
            long a_saved = a;                        /* pshm al/ah/ag */
            a = (long)*(volatile int *)0x57A << 16;  /* ld *(0x57a),16,a */
            a -= (long)*(volatile int *)0x578 << 16; /* sub *(0x578),16,a */
            b = (long)*ar4 * (int)(a >> 16);         /* mpya *ar4 */
            b += 16384;                              /* add #16384,b */
            t = (int)(b & 0xFFFF);                   /* stlm b,t */
            a = a_saved;                             /* popm ag/ah/al */
            a = (long)t * (int)(a >> 16);            /* mpya a (D=0 -> A) */
            a >>= 2;                                 /* sfta a,2 (arith) */
        }
        b = (long)*ar0 * (int)(a >> 16);            /* mpya *ar0+ */
        ar0++;                                       /* + (wrap flagged) */
        b >>= 2;                                     /* sfta b,2 (arith) */
        b += (long)*ar5 << 16;                       /* add *ar5,16,b */
        if ((*(volatile int *)0x3EB5 & 8) != 0) {     /* bitf; bc ntc */
            t = *(volatile int *)0x578;              /* ld *(0x578),t */
            a = (long)*(volatile int *)0x57A << 16;  /* ld *(0x57a),16,a */
            a >>= 2;                                 /* sfta a,2 (arith) */
            b += (long)t * (int)(a >> 16);           /* maca t,b (R=0) */
        }
        a = (long)1023 << 16;                        /* ld #1023,16,a */
        if (b < a)                                   /* min a (signed) */
            a = b;
        b = (long)(unsigned)ar7_live;                /* ldm ar7,b (zero-ext) */
        a -= (long)512 << 16;                        /* sub #512,16,a */
        if ((*(volatile int *)0x17 & 0xFFFF) == 2) { /* cmpm; xc tc below */
            if (a != 0)                              /* xc 1,beq */
                *ar6-- = (int)(((unsigned long)a >> 16) & 0xFFFF);
            *ar1-- = (int)(((unsigned long)a >> 16) & 0xFFFF);  /* xc 1,tc */
        } else {
            if (a != 0)                              /* xc 1,beq */
                *ar6-- = (int)(((unsigned long)a >> 16) & 0xFFFF);
            *ar1++ = (int)(((unsigned long)a >> 16) & 0xFFFF);  /* xc 1,ntc */
        }
    }
    /* ret */
}
