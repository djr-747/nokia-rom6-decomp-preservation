# 00 — What the LEAD is and why it matters

The DCT3 baseband is two processors:

- **MCU** — ARM7TDMI, runs the familiar flash firmware (menus, MMI,
  Layer-2/3, SIM, EEPROM). Fully visible in `.fls` dumps.
- **DSP** — Nokia **LEAD**, a customised **TI TMS320C54x** 16-bit
  fixed-point DSP. Runs the mask ROM in this repo plus C54x code pages
  the MCU uploads at boot. Does GSM Layer-1: GMSK burst shaping,
  synchronisation (FCCH/SCH), equalisation, channel coding, A5/Viterbi,
  A3/A8 cipher, speech transcoding, and RF/baseband control (COBBA,
  synthesizer tuning, RSSI sampling, AFC).

The emulator historically treated the DSP as a behavioural backend.
That works until it doesn't: every unexplained camp/register/call/SMS
failure on ROM6 ends at a DSP stimulus the backend guessed at. This
repo records the silicon's actual contract so guesses become facts.

## ROM revisions

The mask PROM differs by DSP silicon generation, not by phone size —
and one phone model can ship several DSP revisions across builds and
units (confirmed: 8210 carries two block sets; reported: 5110 on
ROM3/ROM4, 8210 on ROM5/ROM6, others likewise). The revision is a
property of the **build + silicon**, never of the model. Fingerprint
every image (`tools/fingerprint.py`); never assume from the model name.

| revision | DSP version at boot | seen in | program image |
|----------|--------------------|---------|---------------|
| ROM4 | 4 | 5110/5110i, 6110, 3210*, 7110, 6150, 5190, 6190 | 65535 words |
| ROM6 | 6 | 3310, 3410, 6210, 8210/8250, 8850, 8290, 8890, 3210* | 65536 words |
| ROM3 | 3? | 5190/6190 (first tables), 6110 (v4.06/v5.47), 6130 (v5.00), 5110 (v5.27) — witnessed by elimination, no image | unsupported slot (witnessed, not recovered) |
| ROM5 | 5? | 8210 (v5.29 set A, by elimination — no image) | unsupported slot (witnessed, not recovered) |

Dual-table club (two block sets, silicon-ID selected): 3210 (ROM4+ROM6
in one image — the cross-generation proof), 8210 (R6+R5), 8290, 8850
(v5.31; v5.11 single), 8890, 5190 (R4+R3 — first table R3 witness),
6190 (same as 5190). Singles so far: 3310, 5110/5110i, 6150.

Fingerprint: uploaded blocks far-branch (`F073` = C54x `B addr`) into
the PROM. Over fully walked tables: ROM4 targets span `0x0926–0xF870`,
ROM6 spans `0x0940–0xFF85`. The band edges discriminate (above `F870`
⇒ ROM6, below `0940` ⇒ ROM4); a mid-band-only table is reported as a
range, not forced. The classifier is validated on 3310 v5.79, 5110
v5.04–v5.30, 8210 v5.11/v5.29/v5.31, 8850 v5.11 — no counter-example in
local images, but a first ROM3/ROM5 table will test it.

## The two halves of "DSP code"

1. **Mask ROM** (`roms/romN/`) — resident PROM/DROM, always present
   (microcomputer mode, MP/MC=0). Interrupt vectors at `0xFF80`, branch
   table at `0xFD00`, superloop/host-ISR/frame-ISR in low PROM.
2. **Paged program API** — C54x blocks in MCU flash, described by a
   flash-resident descriptor table, uploaded over the HPI window into
   DSP DARAM (`0x0800–0x0FFF`) at boot and on demand. They execute in
   place (OVLY=1) and call back into the PROM. Without them the ROM is
   only half the story; see [02-boot-and-upload](02-boot-and-upload.md).

## How Nokia fit GSM in a 90s DSP

The pattern to watch while annotating: ruthless table use (DROM holds
vocoder/codec tables and banked code), interrupt-driven framing (one
frame ISR paces the whole Layer-1), message-ring decoupling from the
MCU (rings, not shared state machines), and pushing policy (what
frequency, what gain, what burst) to the MCU while the DSP owns timing.
Annotate with that lens: *which side decides, which side executes?*
