# 05 — Methodology (how we annotate)

## Confidence levels (mandatory on every symbol/function)

- `verified` — two independent routes agree (e.g. static disasm +
  emulator trace, or disasm + on-hardware capture). Name both.
- `static` — read from disassembly with in-repo reasoning; no dynamic
  confirmation yet.
- `hypothesis` — a guess with a stated falsification (what trace would
  kill it). Never promote without new evidence.

## Rules

1. **Bytes are the contract.** TI docs state intent; the ROM states
   fact. When they disagree, the ROM wins and the doc gets a footnote.
2. **Every address is a word address** unless suffixed `b` (byte).
   C54x is word-addressed; MCU flash offsets are byte addresses. Label
   conversions explicitly.
3. **Big-endian everywhere.** The tic54x BFD is hardwired
   little-endian — byte-swap words before objdump
   (`tools/disasm_c54x.py` does this). A disassembly that wasn't
   byte-swapped is garbage; check the reset vector first
   (`0xFF80` should decode sensibly).
4. **TARG ≠ DSP.** Uploaded blocks link in TARG space and run in DSP
   space with a per-block skew. Always record which space an address
   belongs to.
5. **One claim, one evidence pointer.** Each annotation cites the
   trace/capture/doc that proves it (path + step/offset, not vibes).
6. **Prospective, not retrospective.** A check built from the
   assumption under test proves nothing — confirm against an
   independent oracle (second firmware build, hardware capture, or a
   trace generated before the hypothesis).
7. **No hidden material.** Only public sources: ROM bytes, MCU
   firmware, TI docs, our own traces. Never go looking for grader or
   oracle artefacts.

## Decomp style

- C functions mirror the asm control flow first, bit-exact semantics
  second, elegance never. Name unknowns `unk_<addr>` / `field_<off>`.
- Keep the asm listing next to the C (`roms/romN/asm/` ↔
  `roms/romN/src/`), chunked by region, with a `map.md` cross-index.
- Register/memory effects go in comments at the exact instruction, not
  in a paragraph above the function.
