#!/usr/bin/env python3
"""Verify the ROM images the emulator loader actually uses — plus any local
copies — against the catalog (docs/03-image-catalog.md).

The loader's canonical files live in the sibling emulator checkout
(`firmware/dsp/romN/...`, see --emu-root); this tool checks those first,
because they are the ground-truth bytes the emulator executes. A local
images/ copy, if present, must be byte-identical. Nothing is fetched and
nothing is written — only OK / MISSING / MISMATCH per file.
"""
import argparse
import hashlib
import os
import sys

# name -> (sha256, size or None). Sizes pin the exact loader geometry
# (ROM4 is 65535 physical words + a loader-supplied zero slot).
CATALOG = {
    "rom6": {
        "program.be16": (
            "b450413a3b29a83f691533584f5c923f475e0a720c85acc1ec50097c63eee4cf",
            65536 * 2,
        ),
        "drom.txt": (
            "0e64f8b15ccc46dd17eb72995cd3079432af7afe69e284237d7f962f534d8e1b",
            None,
        ),
        "maskrom-acquired.be16": (
            "fcb9d987110c3288b93b448f2ad5d639399793afff662aa76c20f826de3ed15f",
            None,
        ),
    },
    "rom4": {
        "program.be16": (
            "4a7a9ba9b3b90c732dce8b2f36522ea49249a7b0d1ecbb4538f7fdbb9c51504f",
            65535 * 2,
        ),
        "drom.txt": (
            "998f006dd06c3d73adb1ac7401e50dc42496a95dc3e3a396cf8f0bfad38f5055",
            None,
        ),
    },
}


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def check(path, want, size):
    if not os.path.exists(path):
        return f"MISSING {path}"
    if size and os.path.getsize(path) != size:
        return (f"SIZE-MISMATCH {path}: got {os.path.getsize(path)}, "
                f"want {size}")
    got = sha256(path)
    if got != want:
        return f"HASH-MISMATCH {path}:\n  got  {got}\n  want {want}"
    return f"OK {path}  sha256={got[:12]}... size={os.path.getsize(path)}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", default="rom6")
    ap.add_argument("--emu-root", default="../nokia-dct3-emu",
                    help="sibling emulator checkout owning the loader images")
    ap.add_argument("--dir", default="images",
                    help="optional local copies (must be byte-identical)")
    a = ap.parse_args()

    if a.rom in ("rom3", "rom5"):
        print(f"{a.rom}: unsupported slot, no image catalogued. "
              f"See roms/{a.rom}/README.md.")
        return 0
    if a.rom not in CATALOG:
        sys.exit(f"unknown rom: {a.rom}")

    rc, loader_dir = 0, os.path.join(a.emu_root, "firmware", "dsp", a.rom)
    for name, (want, size) in CATALOG[a.rom].items():
        res = check(os.path.join(loader_dir, name), want, size)
        print(("LOADER " if res.startswith("OK") else "") + res)
        rc = rc or not res.startswith("OK")
        local = os.path.join(a.dir, f"{a.rom}-{name}")
        if os.path.exists(local):
            res = check(local, want, size)
            print(("LOCAL  " if res.startswith("OK") else "") + res)
            rc = rc or not res.startswith("OK")
    return rc


if __name__ == "__main__":
    sys.exit(main())
