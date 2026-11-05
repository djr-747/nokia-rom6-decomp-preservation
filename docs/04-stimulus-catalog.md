# 04 — Stimulus catalog (everything the DSP receives)

Annotate every ROM routine with the stimulus that can reach it. The DSP
has no spontaneous behaviour: interrupt, mailbox, or RF sample causes
each execution. If the trigger isn't named, the annotation isn't done.

## 1. Reset release (MCU `0x20002` bit0 0→1)

Starts the PROM reset vector. Bootstrap DARAM contents are the only
input. Annotate: what the reset path assumes resident.

## 2. HPI doorbell (host→DSP, MCU `0x30000` bit2)

"There is a message / page for you." The DSP's host ISR drains:
(a) the **UPLOADHEADER** 5-word descriptor (`0x87B–0x87F`) during
upload, or (b) the **MDISND ring** (`0x800–0x853`, tail `0x852`, head
`0x853`) in run mode. Every host-ISR annotation must state which phase
it handles and how it distinguishes them.

## 3. MDISND ring entries (M→D messages)

The MCU's command vocabulary: tune/synth programming, burst
descriptors (what to transmit, when), RX measurement requests (RSSI,
which carrier, how many reads), cipher parameters, audio path control,
self-test commands. The per-ROM message table lives in
`roms/romN/messages.md`. Unknown type codes stay `UNKNOWN_xx` with a
capture reference — never guess semantics from one trace.

## 4. MDIRCV ring entries (D→M reports)

The DSP's reply vocabulary: boot-ready version word, RA_INFO
(random-access burst transmitted), measurement results, self-test
verdicts, audio status. Emulator ground truth hinges on exact word
layout here — record bit-level layouts with the trace that proved them.

## 5. Frame interrupt (INT, every GSM frame ≈ 4.615 ms)

The Layer-1 heartbeat. The frame ISR paces burst TX/RX windows, RF
programming lead times, and measurement scheduling. Timing annotations
are in quarter-bit / frame units as the code expresses them; convert
once, at the annotation, and show the arithmetic.

## 6. Uploaded pages (HPI window → DARAM, execute in place)

Overlays at run addresses inside `0x800–0xFFF` (e.g. `0x926`,
`0xD00`, `0xD80`, `0xF00`). From the PROM's view these are
*cross-image calls*: the PROM callee's annotation must name the
calling block(s) and their TARG-space branch sites.

## 7. RF / baseband samples and control reads

COBBA RX samples, RSSI ADC words, synthesizer lock status. The DSP
reads hardware the emulator synthesises; annotate register, width,
rate, and what "no signal" reads as — that value is the emulator's
idle-air default.

### 7a. RF topology split (conditions the whole RF contract)

Two front-end generations, different DSP-visible timing contracts
(emulator ground truth: `dsp54_rf_edge_contract.h`, per-phone binding
in each `models/*/profile.c`):

| topology | RACH TX report | capture lead | phones |
|---|---|---|---|
| PLUSSA_CRFU | request edge | 8 qs, exact | 5110, 5110i, 6110 |
| HAGAR | air edge (P0F) | 64 qs, 2-qs lattice | 8210, 3310 fam, 8850, 8890… |

- COBBA (codec/audio + RX-capture/TX-service path) is common to both;
  the split is the RF front end: PLUSSA/CRFU generation vs HAGAR
  (PLL in the HAGAR IC per the NSM-3 manual).
- HAGAR profile phones: 2100, 3310/15/30/50, 3410, 5210, 5510, 6210,
  6250, 8210, 8250, 8290, 8850, 8855, 8890 (3610 inherits 2100,
  unverified).
- UNKNOWN topology (contract unbound): 3210, 5130, 5190, 6130, 6150,
  6190, 7110, 8810 — note the dual-ROM phones cluster here: the
  front end may vary by silicon/board within one model.
- ROM3/ROM5 have no RACH model (`P04_UNSUPPORTED`); ROM4+UNKNOWN keeps
  the request-edge contract (established for 6150), ROM6 requires an
  explicit board contract.

## 8. Self-test / factory stimulus

The `0x258B` builder path and security-code verdict assembly the MCU
performs on DSP results. A wrong DSP answer here shows up as CONTACT
SERVICE, not as a radio failure — keep verdict paths annotated
separately from traffic paths.
