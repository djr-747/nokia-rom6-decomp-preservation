# ROM4 → ROM6 homology ports (static analogue map)

ROM4 runs in the emulator through calls and SMS. Each analogue below
transfers a behavior hypothesis to ROM6. Grade = source confidence
(HIGH/MED/LOW). Source: emulator `rom6-lowrom-callsite-sigs.md`
(objdump-verified) + rigid-delta map. "Sites" = block:callers.

## Viterbi cluster (dedicated-mode core)

| ROM6 | ROM4 | role | grade |
|---|---|---|---|
| `9042` | `8a3a` | ACS butterfly | HIGH |
| `9217` | `8c0f` | Viterbi init | HIGH |
| `9315` | `8d0d` | traceback (BROM table) | HIGH |
| `929e/92bb/92d7` | `8c96/8cb3/8ccf` | wrap (BRC#9/4/0f) | HIGH |
| `4d9c/4d9d/4da7/4f6e` | `50fd/50fe/5108/5294` | driver slots | HIGH |
| `5a68/5b18/580b` | `5c3a/5cd3/5a41` | dispatch/hook/TC slots | HIGH |

## Control and service

| ROM6 | ROM4 | role | grade |
|---|---|---|---|
| `938c` | `8d84` | McBSP/codec init (port 0 R/W) | HIGH |
| `93ce` | `8db4` | mode dispatch | HIGH |
| `9ddd` | `94b5` | buffer init | HIGH |
| `84af` | `7eb7` | clock/idle cycle | HIGH |
| `851e/8529/853b` | `7f22/7f2d/7f3f` | self-test / service / BROM compute | HIGH |
| `807f` | `7b0a` | gated service | HIGH |
| `2e2f` | `3900` | dispatcher (bare C×20; also resident-ISR callee) | MED-HI |
| `2c88/2c75` | `37ce/37bb` | buffer-op helper / pre-init hook | MED-HI |

## Mid-band port transactions (RF/audio edge candidates)

| ROM6 | ROM4 | role | grade |
|---|---|---|---|
| `4007` | `45c2` | port txn A/B | HIGH |
| `4055` | `4610` | port txn B | HIGH |
| `3c00` | `4282` | consts + flag grammar | HIGH |
| `3d79` | `4414` | const loader | HIGH |
| `388c` | `3ffb` | AR2=#31 + PORTW | HIGH |
| `3e53` | `44b6` | port sequencer | HIGH |
| `3ffa` | `45b5` | AL=#ffff + RPT consts | HIGH |
| `3986` | `407c` | command dispatch | HIGH |
| `ac4c` | `a15f` | port init (7 sites) | HIGH |

## Use rule

Port the ROM4 behavior as hypothesis, then confirm against the ROM6
body word-for-word where the grade is HIGH (the source did for
`8DB4`, `8A3a` cluster). Deltas live in the emulator's relocate map
(Viterbi `+0x608`, trio `+0x5FC`, port-txn `-0x5BB`, `3ffb` `-0x76F`,
`4282` `-0x682`, `94b5` `+0x928`). A port is done when the ROM6 body
is annotated, not when the row is copied here.
