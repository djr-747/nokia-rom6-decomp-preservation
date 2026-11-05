# 06 — Handoff to the emulator (ground truth format)

Findings here become emulator behaviour in `nokia-dct3-emu`. A finding
is "handed off" when it states, in one place:

1. **Stimulus** — which catalog entry (doc 04) triggers it, with exact
   words/bits.
2. **Response** — the DSP's exact observable behaviour (mailbox words,
   timing in frames/quarter-bits, RF programming sequence).
3. **Two routes** — the verification evidence (per doc 05), e.g.
   "static @ `roms/rom6/asm/vectors.lst:FF80` + trace `TA-0142`".
4. **Emulator delta** — which backend file/behaviour changes
   (`mad2_dsp_rom6` vs HLE, message handler, timing constant), as a
   suggestion, not a patch. The emulator stays an independent project;
   we propose, its maintainers dispose.

## Current wall (ROM6): dedicated-mode RF contract

ROM6 registers and runs in the emulator (idle mode + assignment work).
The wall is the **RF contract on MO/MT call and SMS** — what the DSP
demands from RF/baseband once a dedicated channel is up (TCH bring-up,
FACCH/SACCH signalling, UL/DL burst exchange, audio path). Annotate in
this order:

1. Assignment-to-TCH transition: which M→D command moves the DSP to
   dedicated mode, and the exact D→M report that confirms it.
2. Dedicated-mode burst contract: UL burst descriptor layout (what to
   transmit, when, at what power/rate) and DL burst/MDIRCV report
   layout, in frames/quarter-bits as the code expresses them.
3. RF programming lead times: synth/COBBA programming sequence and the
   frame offsets the DSP assumes (PLL lock waits, gain settling).
4. FACCH/SACCH message framing on the DSP side (SMS rides SACCH) —
   word layouts, interleaving expectations, Idle vs dedicated switch.
5. TCH audio path: speech frames DSP↔COBBA routing, mode/rate control.

Idle-mode items (boot handshake, self-test verdict, RSSI scan, RA_INFO
`0x84`) already work end to end in the emulator — annotate them as
backfill, not as wall-breakers.
