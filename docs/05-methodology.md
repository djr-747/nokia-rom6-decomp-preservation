# 05 — Annotation rules

## Confidence levels (mandatory on every symbol/function)

- `verified` — two independent routes agree (static disasm +
  emulator trace, or disasm + on-hardware capture). Name both.
- `static` — read from disassembly with in-repo reasoning; no dynamic
  confirmation yet.
- `hypothesis` — a guess with a stated falsification (what trace would
  kill it). Never promote without new evidence.

## Rules

1. **Bytes are the contract.** TI docs state intent; the ROM states
   fact. When they disagree, the ROM wins. The doc gets a footnote.
2. **Every address is a word address** unless suffixed `b` (byte).
   C54x is word-addressed; MCU flash offsets are byte addresses. Label
   conversions explicitly.
3. **Big-endian everywhere.** The tic54x BFD is hardwired
   little-endian. Byte-swap words before objdump
   (`tools/disasm_c54x.py` does this). A disassembly that was not
   byte-swapped is unusable. Check the reset vector first.
   `0xFF80` must decode sensibly.
4. **TARG ≠ DSP.** Uploaded blocks link in TARG space and run in DSP
   space with a per-block skew. Always record which space an address
   belongs to.
5. **One claim, one evidence pointer.** Each annotation cites the
   trace/capture/doc that proves it (path plus step/offset, not
   memory).
6. **Prospective, not retrospective.** A check built from the
   assumption under test proves nothing. Confirm against an
   independent oracle. Use a second firmware build, a hardware
   capture, or a trace generated before the hypothesis.
7. **No hidden material.** Only public sources: ROM bytes, MCU
   firmware, TI docs, our own traces. Never go looking for grader or
   oracle artefacts.

## Annotation order (bring-up sequence)

Annotate in the order the phone executes. Never jump to dedicated
mode first. Each stage gates the next; a late-stage annotation that
assumes an unannotated early stage is unsound.

1. Reset + loader (`0xFF80` → `0x0F00`, clocks, DARAM zero, vector
   copy, IPTR set, mini-kernel copy). Grounds every address that
   follows.
2. Upload handshake (header engine, version publish). Grounds the
   MCU→DSP contract.
3. Self-test (`0x258B` path, verdict assembly). A wrong reading here
   shows CONTACT SERVICE, not a radio fault. Keep verdict paths
   separate from traffic paths.
4. Identity provisioning (calibration checksum, `dsp_uploaded` flag,
   MMI-ready byte, SIM-lock dance, Kc handover). The dance, post warm
   reboot: NVRAM holds the simlock config; MCU configures identity
   (MSID, 13 bytes); DSP validates against its COBBA ID; MCU sends lock
   data; DSP decodes it and returns lock data; MCU verifies and allows
   the SIM. Observed opcodes (emulator, static confirmation open):
   M→D sub `0x13` (seed/MSID setup), D→M `0x34` (`34 0E 00 <msid…>`).
   IMEI build (`GU3_LOCALSEC_IMEI15_BUILD`) and lock evaluation
   (`GU2_SIMLOCK_EVAL`, gate `0x21C630` on 3310 v5.79) run MCU-side;
   decode plus COBBA-ID check run DSP-side. Both halves need grounding
   before claiming what "unlocks" the DSP.
5. Tuning (NVRAM tune config → DSP records). Per-phone RF calibration
   (AFC, AGC, TX levels) crosses in MDISND tune records at boot.
   Backing store is per-model profile ground truth: I2C EEPROM on
   3210, 5110 family, 6110/6130, 6150, 6190, 8810; in-flash EEPROM on
   the rest. tuning opcodes are open; the per-build data pages
   (`block04/17` shape) are not the per-phone NVRAM values. Do not
   confuse them.
5. Idle (frame ISR at rest, paging, measurements, neighbor list).
6. Traffic setup (RACH, assignment, ciphering).
7. Dedicated mode (TCH/FACCH/SACCH, voice path). Last, not first.

## Decomp style

- C functions mirror the asm control flow first, bit-exact semantics
  second, elegance never. Name unknowns `unk_<addr>` / `field_<off>`.
- Keep the asm listing next to the C (`roms/romN/asm/` ↔
  `roms/romN/src/`), chunked by region, with a `map.md` cross-index.
- Register/memory effects go in comments at the exact instruction, not
  in a paragraph above the function.
