# 03 — Image catalog (the loader's bytes)

The emulator loader's canonical files live in the sibling checkout at
`firmware/dsp/romN/`. `tools/verify_images.py` checks those paths
first — they are the ground-truth bytes the emulator executes — then
any local `images/` copies (which must be byte-identical). Nothing
under `images/` is committed. `make verify` covers both.

## ROM6 (active)

| file | SHA-256 | role |
|------|---------|------|
| `firmware/dsp/rom6/program.be16` | `b450413a3b29a83f691533584f5c923f475e0a720c85acc1ec50097c63eee4cf` | 65536-word runtime program space, BE words |
| `firmware/dsp/rom6/drom.txt` | `0e64f8b15ccc46dd17eb72995cd3079432af7afe69e284237d7f962f534d8e1b` | data-ROM text dump (== acquisition view) |
| `firmware/dsp/rom6/maskrom-acquired.be16` | `fcb9d987110c3288b93b448f2ad5d639399793afff662aa76c20f826de3ed15f` | mask-ROM rows view (acquisition input) |

Caution: the raw acquisition program view
(`analysis/dsp/rom6/acquisition/program.be16`, `ccb40065…59782af7`)
is *not* the runtime image — the loader's `program.be16` above is the
promoted reconstruction. Never substitute one for the other.

## ROM4 (parked)

| file | SHA-256 | role |
|------|---------|------|
| `firmware/dsp/rom4/program.be16` | `4a7a9ba9b3b90c732dce8b2f36522ea49249a7b0d1ecbb4538f7fdbb9c51504f` | 65535 words + loader-supplied zero slot, BE |
| `firmware/dsp/rom4/drom.txt` | `998f006dd06c3d73adb1ac7401e50dc42496a95dc3e3a396cf8f0bfad38f5055` | data-ROM text dump |

ROM4 is intentionally 65535 physical words; the loader supplies the
zero-filled 65536th slot. Do not pad or rewrite the file.

## ROM3 / ROM5

No recovered image. Their `roms/` slots document the expected geometry
(64K-word C54x program space, BE) so a future dump plugs straight into
`verify` + `disasm`. Add the SHA-256 here the day one lands.

## Paged program images (all revisions)

Extracted from your own MCU `.fls` dumps — never shipped:

```sh
# one table per invocation; dual-table builds need two runs
python3 tools/fingerprint.py --fls /path/to/3310-v5.79.fls  # find tables
python3 tools/extract_blocks.py --fls /path/to/3310-v5.79.fls \
    --table 0x300CD8 --out build/rom6/blocks/
```

Output is one `blockNN.bin` per payload block (BE words, as in flash —
note the emulator's `re/dsp/*.bin` files are byte-swapped LE, not
canonical) + `manifest.json` with every descriptor
(`flash/entry/ctrl/size/dest/len` + `placeholder` flag). Commit the
manifest per build (see `roms/romN/blocks/`); `.bin` payloads stay in
`build/`.
