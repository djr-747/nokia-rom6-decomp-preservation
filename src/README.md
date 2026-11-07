# Source tree

DSP-arch layout. One directory per ROM revision; shared facts live in
`common/`. Subsystem directories follow the decomp bring-up order and the
docs (`docs/00-overview.md` to `docs/08-selector.md`).

```
src/
  common/
    include/      MMR / DARAM / HPI map headers (all revisions)
  rom6/
    link/         rom6.cmd -- MEMORY/PAGE layout (C542, OVLY end 0x2000)
    boot/         reset path, overlay loader, uploaded-page entry
    kernel/       superloop, ISRs, dispatchers, shared spine routines
    modem/        frame ISR consumers, Viterbi/equalizer, MAC engines
    audio/        audio engine, tone/voice path
    rf/           COBBA/HAGAR drivers, tuning, RSSI/camping posters
    msg/          MDI builders, HPI mailbox, identity/tune traffic
    tables/       .word data tables (coefficients, jump tables)
```

## Module rules

- One `.asm` per claimed symbol span, named `<addr>_<symbol-lower>.asm`.
- Header comment: ROM6 address, symbol name, word count, evidence wave.
- `; ORIGIN 0xXXXX` line: required. `tools/recombine.py` assembles the
  file with `tic54x-as` and byte-compares against the loader image slice.
- Absolute call/branch targets assemble as-is (single-page C542, no XPC).
- Every file carries `.mmregs` (gas rejects ST0/ST1/accumulators without it).
- Port addresses are numeric (`portw *(0xc),49`): the `paNN` form objdump
  prints silently misencodes to port 0 under gas. The recombine byte-compare
  is the guard; never commit a module that does not MATCH.
- Placement: put the file where the symbol's evidence points; generic
  spine routines live in `kernel/` until trace or cross-refs promote them.
- C sources (goal: byte-identical recompilation) sit beside the `.asm`
  they specify, same basename, `.c` extension. The `.asm` is the verified
  encoding; the `.c` states intent in TI C54x dialect until `cl500` closes
  the codegen loop. See `docs/09-recompilation.md`.
