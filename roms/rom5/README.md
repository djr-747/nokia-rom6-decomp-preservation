# ROM5 — witnessed, no image

No recovered ROM5 mask image exists. Seventeen witness tables exist:
8210 (v5.11-v5.31, eleven builds), 8290 (v5.22), 8850 (v5.11, v5.26,
v5.31 ×2), 8890 (v12.16).

Witness shape (doc 07): ROM6 band (`0940-FF85`), 19 payload words,
`R4ref=0`, `R6ref=0`, miss ~8-10/31-38. Not ROM4, not ROM6, too late
for ROM3: closed set `{3,4,5,6}` leaves 5.

Mechanism (doc 08): the 8210 gate serves this set when the DSP reports
version 5 (`==5` → cell `0x135810` → first table e.g. `0x30DD68` on
v5.29). R5 is the set a version-5 DSP is served. PROM overlap with the
validated ROM6 set is zero.

ROM5 shares the ROM3 landing checklist: geometry, SHA-256 in doc 03,
`verify` plus `disasm` support, `roms/rom6/` mirror, and a fingerprint
range below the ROM6 band. Expect call-site overlap with ROM6 (shared
lineage); the discriminator is zero ref overlap plus high operand
miss, not band alone.
