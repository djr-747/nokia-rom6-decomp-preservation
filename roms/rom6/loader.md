# Loader1 + version publisher (block00 tail / block48, 3310 v5.79)

Two payloads share run address `0x0F00` in sequence. Phase 1
(block00 tail, 119 + 7 words) boots and uploads. Phase 2 (block48,
223 words) re-inits, publishes the version, and takes over the
upload loop. Same address, two phases; symbols carry the phase.

## FLS source of the `0x0D00` staging (closed)

The 421 words loader1 copies `0x0D00→0x0590` are the head of the
block00 payload: first word `0xFC00` matches `block00.bin` word 0
and the emulator's live observation `0xD00=0xFC00` (emulator
`src/dsp/c54x/mad2_dsp_c54x.c`, reset-trace comment; placement
note in `src/dsp/c54x/dct3_dsp54.c`). Same copy on 6110
(`stm #0xD00,ar2 … mvdp *ar2+,0x590`, emulator
`docs/dsp-blocks-re-3310.md`). Flash bytes: 3310 v5.79 FLS, DSP table `0x300CD8` block idx 0
at flash 3149016, dest `0x500` (runtime `0x0800 + dest` =
`0x0D00`, the exact MVDP source — extractor docstring rule,
confirmed). First 421 words of its 638-word payload feed the
copy. The HPI hardware boot stages that payload at DSP `0x0D00`
before reset release (documented for 5110 in emulator
`docs/dsp-boot-upload-architecture.md` §6; on 3310 the dest
rule plus the `0xFC00` match close it with no inference step
left on placement).

## Phase 1 — LOADER1_ENTRY `0x0F00-0x0F76` (block00, file off `0x200`)

| addr | code | effect |
|---|---|---|
| `0x0F00` | `STM #705,SP` | stack top `0x02C1` |
| `0x0F02` | `STM #8192,SWWSR` | external wait states |
| `0x0F04` | `SSBX CPL` | compiler mode on |
| `0x0F05` | `STM #20974,CLKMD` | PLL on (`0x51EE`) |
| `0x0F07` | `MVDM 0x4F7/0x4F8 → AR4/AR5` | save peripheral regs |
| `0x0F0B` | `RPTZ, STL *AR3+` ×1952 | zero DARAM `0x0060+` |
| `0x0F10` | `RPTZ, STL *AR3+` ×12288 | zero DARAM `0x1000+` |
| `0x0F15` | `A=-25+128; AR1=A` | copy count 103 (`*(0x11)` = AR1, RPT reads it) |
| `0x0F1A` | `AR2=0x0780; RPT AR1; MVPD 0xFF80→*AR2+` | mask vectors → DARAM `0x0780` (26 slots) |
| `0x0F20` | `STM #0x07A8,PMST` | IPTR `0x0F`, OVLY/DROM on. Runtime base `0x0780` |
| `0x0F22` | `MVMD AR4/AR5 → 0x4F7/0x4F8` | restore peripheral regs |
| `0x0F26` | `A=1845-1424; AR1=A` | copy count 421 |
| `0x0F2B` | `AR2=0x0D00; RPT AR1; MVDP *AR2+→0x590` | block00 → mini-kernel `0x0590` via program bus (OVLY RAM) |
| `0x0F31` | `ST #0,*(0x872); ST #20,*(0x871)` | reply 0, request `0x14` |
| `0x0F37` | `ORM/ANDM *(0x29)` | toggle control flag |
| `0x0F3D` | `CALL 0x0F77` | wait for MCU ack |
| `0x0F3F` | upload engine | header at `0x87B-0x87F`, `MVDD` copy loop, `BC 0x0A00` when done |

## WAIT_ACK_SUB `0x0F77-0x0F7D`

Polls `*(0x872)==0`, returns when the MCU acks. 7 words, ends the
block with `RET`.

## Phase 2 — BOOT_PUBLISH_ENTRY `0x0F00-0x0FDE` (block48, 223 words)

| addr | code | effect |
|---|---|---|
| `0x0F00` | `SSBX INTM` | interrupts off |
| `0x0F01` | `STM SP/SWWSR/CLKMD; STM #0xFFA8,PMST` | re-init, IPTR back `0x1FF` (mask vectors live during upload) |
| `0x0F09` | `RPT #320; NOP` | settle delay |
| `0x0F0C` | `ST #6,*(0x803)` | HPI word 3 = 6 |
| `0x0F0F` | `MVDP *(0x803)→0xFF87` | word to program space (quirk, keep verbatim) |
| `0x0F12` | `MVPD 0xFF87→*(0x802)` | mask version constant → HPI word 2. `0xFF87` = 6 on ROM6, 4 on ROM4 |
| `0x0F15` | `CALL 0x0F67` | seeds `*(0x60/0x61)` (see below) |
| `0x0F17` | upload engine (mirrors phase 1 from `LD *(0x87F)`) | same loop, same exit to `0x0A00` |

Version path, closed: mask `0xFF87` → `*(0x802)` = HPI word 2 =
MCU `[0x10004]` → version word → set gate (doc 08).
`MVDP→0xFF87` quirk, closed: the C54x has no data→data HPI
move. `MVDP Smem,PMST` (data→program) plus `MVPD PMST,Smem`
(program→data) is the only copy path from HPI word 3 to word
2, so the word parks in program-far scratch `0xFF87`. Same
write-then-read-back idiom appears in the uploaded selftest
builder (`mvdp [0x60]→0xff87`, `mvpd 0xff87→staging`,
emulator `docs/research/selftest-DEEP-…§2.2`). Keep the two
instructions verbatim on recompile: the scratch address is
load-bearing.

## VITERBI_SEED_SUB `0x0F67-0x0F6D` (block48)

`LD #23065,16,a; OR #31533,a; DST a,*(0x60); RET`.
Seeds the Viterbi save cells with `0x7B2D5A19`. Confirms
`VITERBI_STATE` (`symbols.yaml`) is a 32-bit cell pair.
Follower at `0x0F70`: `DLD *(0x60),a; AR3=0x0F6E; AR2=1;
CALL 0xFCC; RET` (compare stub, callee body open), then NOP
sled, `STM #-96,PMST`, `B 0x0F00` reset loop, and the
`PORTW pa0` upload-engine head (`LD #13,a`, RPT #22).
