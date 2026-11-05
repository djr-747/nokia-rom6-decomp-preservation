# ROM6 vectors (`0xFF80–0xFFFF`) — verified baseline

Source: `images/rom6-program.be16` (SHA-256 `b45041…eee4cf`), words read
big-endian; disassembly via byte-swapped tic54x objdump
(`build/rom6/vectors.lst`, gitignored — regenerate with
`make disasm-rom6`).

## Slot layout: 4 words per vector (`IPTR=0x1FF` → base `0xFF80`)

## Vector 0 — RESET @ `0xFF80` (verified)

```
FF80: 771D FFA8      STM  #0xFFA8, PMST     ; OVLY=1, MP/MC=0, DROM=1, IPTR=0x1FF
FF82: F073 FF85      B    0xFF85            ; into the next slot's middle
```

Two independent routes agree on the decode: the tic54x BFD
(`771D`=STM, `F073`=B) and the TDD reference core
(`~/projects/ti-c54x`, opcode catalog `RETF=0xF49B` family context;
STM/B are its baseline covered ops). The `PMST=0xFFA8` value matches
the firmware-correlated boot config in `docs/01-memory-map.md`.

## Vector 1 — trampoline + unhandled-interrupt stub @ `0xFF84` (verified decode, role static)

```
FF84: F49B           RETF                  ; fast return, no INTM change
FF85: F073 0F00      B    0x0F00            ; reset lands HERE from FF82
FF87: 0006           (padding, unexecuted)
```

Reset flow: `FF80 STM` → `FF82 B FF85` → `FF85 B 0F00` → **DARAM
`0x0F00`**, i.e. straight into MCU-uploaded code. `0x0F00` lies inside
the block00 footprint (DSP `0x0D00–0x0F7E`, branch table + loader1 —
see `blocks/3310-v5.79-manifest.json`), so the mask ROM boots by
delegating to the paged program API, not by running resident init.

Every other dumped slot (`FF88`, `FF8C`, …) reads `F49B F495 F495
F495` = `RETF; NOP; NOP; NOP`: unhandled interrupts return
immediately. Hypothesis (falsifiable): slot assignment follows the
C54x order (1=NMI?), to be pinned against SPRU131G §5; only vector 0's
role is load-bearing today.

## What this means for the emulator wall

- The release-edge model (PC=`0xFF80`, `PMST` set by the ROM itself)
  is correct — the co-sim must not pre-set PMST side effects the STM
  would perform.
- The first stimulus the ROM needs is not a mailbox message but the
  uploaded page containing `0x0F00`. A ROM6 boot that never receives
  block00 cannot proceed past `FF85` by construction.
- Next annotation target, in wall order: block00's code at `0x0F00`
  (loader1) and the PROM callees it far-branches into.
