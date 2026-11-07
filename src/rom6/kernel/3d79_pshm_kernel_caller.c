/* ROM6 ORIGIN 0x3D79 (218w): PSHM_KERNEL_CALLER -- pshm prelude + PA33/43/3/10/11/9 tail.
 * Verified encoding: src/rom6/kernel/3d79_pshm_kernel_caller.asm (recombine MATCH).
 * EXPECT: F074 063C 4A10 4A08 4A09 4A0A 7710 263B F210 03CF F310 007C FF42 F120 FFFF F495 F495 8A0A 8A09 8A08 6880 FFFB FF4F 6980 0004 F130 0002 F84D 3D98 7313 0231 7312 0230 7710 022C 8090 61F8 3EC8 0020 F110 0001 F820 3DA6 F84D 3DA8 7080 3E9A 6D88 1090 F130 0008 F84D 3DB5 76F8 022F 0001 4488 F074 3CD2 1080 F130 0001 F84D 3DD5 61F8 3EC8 0020 F820 3DC6 F130 0008 F84C 3DC6 44F8 022D F074 3CD2 F120 0080 7710 0518 8190 8190 F120 0100 8190 8180 68F8 051D FFFD F073 3DFD F110 0002 F84C 3DF6 44F8 2490 71F8 2490 022D 61F8 3EC8 0020 F820 3DF2 60F8 250F 0022 F820 3DF2 60F8 34BF 0004 F820 3DF2 44F8 3491 71F8 3491 022D F074 3CD2 F073 3DFD F130 0004 F84D 3DFD 76F8 022E 0004 76F8 022A 0001 E900 7710 0228 4F90 69F8 051D 0010 68F8 051D FFFE F074 25D9 61F8 0007 0800 F7BB 74F8 0008 0021 F040 0200 F495 75F8 0008 0021 FD20 F6BB 4911 09F8 3EA7 F84A 3E22 01F8 036A F495 75F8 000B 000A EC15 F495 F120 3A98 F495 75F8 000B 000B EC16 F495 F495 75F8 0011 0009 EC13 F495 61F8 0007 0800 F7BB 74F8 0008 002B F040 0200 F495 75F8 0008 002B F495 74F8 0008 0003 F040 0005 F495 75F8 0008 0003 EC0E F495 FD20 F6BB 8A10 FC00
 *
 * Intent: dark head call 0x063C, then pshm ar0/al/ah/ag (AR0 and A
 * saved, restored before use/return). A = B - 975; B -= 124; A >= 0
 * loads B = -1 (xc 2,ageq, COND 0x42 per oracle branch table). A
 * restored (popm); cell 0x263B bit 2 = (B <= 0) (andm plus xc 2,bleq
 * over the orm, COND 0x4F). B = A & 2; zero skips the AR3 snapshot
 * (bc beq to 0x3D98): cell 0x231 = AR3-value, cell 0x230 = AR2-value
 * (mvmd; AR2/AR3 caller-live values, read-only). AR0 = 0x22C;
 * cell 0x22C = A-low. TC = cell 0x3EC8 bit 5; B = A - 1; !TC detours
 * to the 0x3DA6 merge (bc ntc); A == 1 joins 0x3DA8 (bc beq), else
 * cell 0x22D = cell 0x3E9A (mvkd). Merge: AR0--, A = cell 0x22C,
 * AR0++. B = A & 8; zero joins 0x3DB5 (bc beq), else cell 0x22F = 1,
 * A = cell 0x22D << 16, dark PORT4850_SEQ call (A-live long contract;
 * B/AR liveness flagged), A = cell 0x22C. 0x3DB5: B = A & 1; zero
 * joins 0x3DD5 (bc beq), else TC re-read; !TC or (A & 8) joins 0x3DC6
 * (bc ntc / bc bneq), else A = cell 0x22D << 16 and a second
 * PORT4850_SEQ call. 0x3DC6: B = 128 (ld #128,b; ROM word F120 forced
 * in the .asm, gas would emit E980 -- intent per the forced note);
 * cells 0x518/0x519 = 128, B = 256, cells 0x51A/0x51B = 256;
 * cell 0x51D &= -3; branch 0x3DFD. 0x3DD5: B = A - 2; nonzero joins
 * 0x3DF6 (bc bneq), else A = cell 0x2490 << 16, cell 0x22D = cell
 * 0x2490; TC clear, marker != 34, or mode != 4 keep that A and call
 * PORT4850_SEQ at 0x3DF2, else A = cell 0x3491 << 16,
 * cell 0x22D = cell 0x3491, same call. 0x3DF6: B = A & 4; zero joins
 * 0x3DFD (bc beq), else cell 0x22E = 4. 0x3DFD: cell 0x22A = 1; B = 0;
 * 32-bit store of B to cells 0x228/0x229 (dst, per op_dst); cell 0x51D
 * |= 16 then &= -2; dark call 0x25D9. PA33 stanza (TC = cell 7 bit 11):
 * A = PA33 with AL-alias write, A |= 512, PA33 = A, 2 settle nops;
 * !TC keeps INTM = 1 else INTM = 0 (xc 1,ntc over rsbx, 39A4
 * precedent). Dead-B adjust lane: B = AR1 - cell 0x3EA7, plus cell
 * 0x36A if negative (bc bgeq; B dead after, flagged). PA10 =
 * cell 0x0B; 22 settle nops; B = 15000 (dead: portw reads cell 0x0B,
 * not B, flagged); PA11 = cell 0x0B; 23 + 1 settle nops; PA9 =
 * cell 0x11; 20 settle nops. PA43 stanza (TC re-read): A = PA43 |
 * 512 write-back with alias; PA3 stanza: A = PA3 | 5 write-back;
 * 15 settle nops; !TC keeps INTM = 1 (xc 1,ntc). AR0 restored, ret.
 * Live-ins are read after the dark 0x063C head (values post-call,
 * flagged); AR0/A restored at return, B/AR1 dead (flagged).
 */
extern void sub_063C(void);
extern void sub_3CD2(long a_live);
extern void sub_25D9(void);
extern int port_read_33(void);
extern void port_write_33(int v);
extern int port_read_43(void);
extern void port_write_43(int v);
extern int port_read_3(void);
extern void port_write_3(int v);
extern void port_write_10(int v);
extern void port_write_11(int v);
extern void port_write_9(int v);

void pshm_kernel_caller_3D79(long a_live_in, long b_live_in,
                             int ar1_in, int ar2_in, int ar3_in)
{
    long a = a_live_in;
    long b = b_live_in;
    int tc;
    int *ar0;

    sub_063C();                                        /* call 0x63c (dark) */
    /* pshm ar0/al/ah/ag (saved; AR0/A restored before use/return) */
    ar0 = (int *)0x263B;                               /* stm #9787,ar0 */
    a = b - 975L;                                      /* sub #975,b,a */
    b = b - 124L;                                      /* sub #124,b */
    if (a >= 0)                                        /* xc 2,ageq */
        b = -1L;                                       /* ld #-1,b */
    /* nop; nop */
    /* popm ag/ah/al (A restored) */
    *ar0 &= -5;                                        /* andm #-5,*ar0 */
    if (b <= 0)                                        /* xc 2,bleq */
        *ar0 |= 4;                                     /* orm #4,*ar0 */
    b = a & 2L;                                        /* and #2,a,b */
    if ((b & 0xFFFF) != 0) {                           /* bc 0x3d98,beq */
        *(volatile int *)0x231 = ar3_in;               /* mvmd ar3,0x231 */
    }
    /* 0x3d98 join */
    *(volatile int *)0x230 = ar2_in;                   /* mvmd ar2,0x230 */
    ar0 = (int *)0x22C;                                /* stm #556,ar0 */
    *ar0++ = (int)(a & 0xFFFF);                        /* stl a,*ar0+ */
    tc = (*(volatile int *)0x3EC8 & 32) != 0;          /* bitf */
    b = a - 1L;                                        /* sub #1,a,b */
    /* bc 0x3da6,ntc lands ON the mvkd; bc 0x3da8,beq skips it. */
    if (!tc || (b & 0xFFFF) != 0) {
        *(volatile int *)0x22D = *(volatile int *)0x3E9A; /* mvkd 0x3e9a,*ar0 */
    }
    /* 0x3da6/0x3da8 join */
    ar0--;                                             /* mar *ar0- */
    a = (long)*ar0++;                                  /* ld *ar0+,a */
    b = a & 8L;                                        /* and #8,a,b */
    if ((b & 0xFFFF) != 0) {                           /* bc 0x3db5,beq */
        *(volatile int *)0x22F = 1;                    /* st #1,*(0x22f) */
        a = (long)*(volatile int *)0x22D << 16;        /* ld *ar0-,16,a */
        ar0--;
        sub_3CD2(a);                                   /* call 0x3cd2 */
        a = (long)*ar0;                                /* ld *ar0,a */
    }
    /* 0x3db5 join */
    b = a & 1L;                                        /* and #1,a,b */
    if ((b & 0xFFFF) != 0) {                           /* bc 0x3dd5,beq */
        tc = (*(volatile int *)0x3EC8 & 32) != 0;      /* bitf */
        b = a & 8L;                                    /* and #8,a,b */
        if (tc && (b & 0xFFFF) == 0) {
            a = (long)*(volatile int *)0x22D << 16;    /* ld *(0x22d),16,a */
            sub_3CD2(a);                               /* call 0x3cd2 */
        }
        /* 0x3dc6 join */
        b = 128L;                                      /* ld #128,b (F120 forced) */
        ar0 = (int *)0x518;                            /* stm #1304,ar0 */
        *ar0++ = (int)(b & 0xFFFF);                    /* stl b,*ar0+ */
        *ar0++ = (int)(b & 0xFFFF);                    /* stl b,*ar0+ */
        b = 256L;                                      /* ld #256,b */
        *ar0++ = (int)(b & 0xFFFF);                    /* stl b,*ar0+ */
        *ar0 = (int)(b & 0xFFFF);                      /* stl b,*ar0 */
        *(volatile int *)0x51D &= -3;                  /* andm #-3 */
    } else {
        /* 0x3dd5 lane */
        b = a - 2L;                                    /* sub #2,a,b */
        if ((b & 0xFFFF) != 0) {                       /* bc 0x3df6,bneq */
            /* 0x3df6 lane */
            b = a & 4L;                                /* and #4,a,b */
            if ((b & 0xFFFF) != 0)                     /* bc 0x3dfd,beq */
                *(volatile int *)0x22E = 4;            /* st #4,*(0x22e) */
        } else {
            a = (long)*(volatile int *)0x2490 << 16;   /* ld *(0x2490),16,a */
            *(volatile int *)0x22D = *(volatile int *)0x2490; /* mvdk */
            tc = (*(volatile int *)0x3EC8 & 32) != 0;  /* bitf */
            if (tc && *(volatile int *)0x250F == 34 &&
                    *(volatile int *)0x34BF == 4) {
                a = (long)*(volatile int *)0x3491 << 16; /* ld *(0x3491),16,a */
                *(volatile int *)0x22D = *(volatile int *)0x3491; /* mvdk */
            }
            /* 0x3df2 join */
            sub_3CD2(a);                               /* call 0x3cd2 */
        }
    }
    /* 0x3dfd join */
    *(volatile int *)0x22A = 1;                        /* st #1,*(0x22a) */
    b = 0L;                                            /* ld #0,b */
    ar0 = (int *)0x228;                                /* stm #552,ar0 */
    *ar0++ = (int)((b >> 16) & 0xFFFF);                /* dst b,*ar0+ (high) */
    *ar0++ = (int)(b & 0xFFFF);                        /* dst (low) */
    *(volatile int *)0x51D |= 16;                      /* orm #16 */
    *(volatile int *)0x51D &= -2;                      /* andm #-2 */
    sub_25D9();                                        /* call 0x25d9 (dark) */
    tc = (*(volatile int *)0x7 & 2048) != 0;           /* bitf *(0x7),#2048 */
    /* ssbx st1,intm (hardware, no C form) */
    a = (long)port_read_33();                          /* portr 33,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);          /* AL alias write */
    a |= 512L;                                         /* or #512,a */
    /* nop */
    port_write_33((int)(a & 0xFFFF));                  /* portw *(0x8),33 */
    if (!tc) {                                         /* xc 1,ntc */
        /* rsbx st1,intm (hardware state) */
    }
    b = (long)(unsigned)ar1_in;                        /* ldm ar1,b */
    b -= (long)*(volatile int *)0x3EA7;                /* sub *(0x3ea7),b */
    if (b < 0)                                         /* bc 0x3e22,bgeq */
        b += (long)*(volatile int *)0x36A;             /* add *(0x36a),b */
    /* 0x3e22 join; nop; B dead from here (flagged) */
    port_write_10(*(volatile int *)0xB);               /* portw *(0xb),10 */
    /* rpt #21 nop: 22 settle cycles */
    /* nop */
    b = 15000L;                                        /* ld #15000,b (dead, flagged) */
    /* nop */
    port_write_11(*(volatile int *)0xB);               /* portw *(0xb),11 */
    /* rpt #22 nop: 23 settle cycles */
    /* nop; nop */
    port_write_9(*(volatile int *)0x11);               /* portw *(0x11),9 */
    /* rpt #19 nop: 20 settle cycles */
    tc = (*(volatile int *)0x7 & 2048) != 0;           /* bitf *(0x7),#2048 */
    /* ssbx st1,intm (hardware, no C form) */
    a = (long)port_read_43();                          /* portr 43,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);          /* AL alias write */
    a |= 512L;                                         /* or #512,a */
    /* nop */
    port_write_43((int)(a & 0xFFFF));                  /* portw *(0x8),43 */
    /* nop */
    a = (long)port_read_3();                           /* portr 3,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);          /* AL alias write */
    a |= 5L;                                           /* or #5,a */
    /* nop */
    port_write_3((int)(a & 0xFFFF));                   /* portw *(0x8),3 */
    /* rpt #14 nop: 15 settle cycles */
    /* nop */
    if (!tc) {                                         /* xc 1,ntc (FD20) */
        /* rsbx st1,intm (hardware state) */
    }
    /* popm ar0 (AR0 restored) */
    /* ret */
}
