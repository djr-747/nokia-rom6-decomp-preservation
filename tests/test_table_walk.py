#!/usr/bin/env python3
"""Regression tests for the DSP block-table walker (tools/fingerprint.py).

Uses a synthetic flash image — no ROM bytes. Covers the None-end bug
(walk must return an int end offset, never None) and the two
mis-walk shapes seen on real images: inter-block zero padding and a
trailing code window that mimics a header (entry==0).
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "..", "tools"))
from fingerprint import FLASH_BASE, is_data, header_at, walk


def hdr(entry, ctrl, size, dest, blen):
    return struct.pack(">6H", entry, ctrl, size, dest, blen, 0)


def build_image():
    # 0xFF background like trailing flash code: nothing in it may read
    # as a header (entry 0xFFFF is refused) or as padding (no zero runs).
    img = bytearray([0xFF]) * 0x1000
    o = 0x100
    # block 0: loader header + 4 payload words (incl. an F073 target)
    img[o:o + 12] = hdr(0xFD00, 0xFF80, 4, 0x500, 0x78)
    img[o + 12:o + 20] = struct.pack(">4H", 0xF073, 0xFF85, 0xF495, 0xF495)
    o += 12 + 8
    # 2-word zero gap (as observed after real blocks)
    img[o:o + 4] = b"\x00\x00\x00\x00"
    o += 4
    # placeholder slot with retained entry/dest (size 0)
    img[o:o + 12] = hdr(0x09C6, 0x0B39, 0, 0x1C6, 0x4EC)
    o += 12
    # block 1: real payload
    img[o:o + 12] = hdr(0x09C6, 0x0B39, 2, 0x1C6, 0x04)
    img[o + 12:o + 16] = struct.pack(">2H", 0xF073, 0x0ABC)
    o += 12 + 4
    # trailing code that mimics a header but has entry==0 (must be refused)
    img[o:o + 12] = struct.pack(">6H", 0x0000, 0x0000, 0x002B, 0xB744,
                                0x0000, 0x0000)
    return bytes(img), o


def test_walk_end_is_int_offset():
    buf, _ = build_image()
    blocks, end = walk(buf, 0x100, 64)
    assert isinstance(end, int), f"walk end must be int, got {end!r}"
    assert end > 0x100


def test_walk_finds_loader_and_blocks():
    buf, _ = build_image()
    blocks, _ = walk(buf, 0x100, 64)
    data = [b for b in blocks if not b["placeholder"]]
    assert len(data) == 2, f"want 2 payload blocks, got {len(data)}"
    assert [b["entry"] for b in data] == [0xFD00, 0x09C6]
    assert [b["flash"] - FLASH_BASE for b in data] == [0x100, 0x100 + 12 + 8 + 4 + 12]


def test_walk_records_placeholder():
    buf, _ = build_image()
    blocks, _ = walk(buf, 0x100, 64)
    ph = [b for b in blocks if b["placeholder"]]
    assert len(ph) == 1 and ph[0]["entry"] == 0x09C6


def test_entry_zero_header_is_not_data():
    buf, fake = build_image()
    h = header_at(buf, fake)
    assert h is not None and h["entry"] == 0x0000
    assert not is_data(buf, fake, h)


def test_loader_gate_rejects_non_table():
    buf = bytes(0x1000)
    blocks, _ = walk(buf, 0x100, 64)
    assert blocks is None


def build_two_adjacent():
    img = bytearray([0xFF]) * 0x1000
    img[0x100:0x10C] = hdr(0xFD00, 0xFF80, 1, 0x500, 0x78)
    img[0x10C:0x10E] = struct.pack(">H", 0xF495)
    img[0x10E:0x11A] = hdr(0xFD00, 0xFF80, 1, 0x500, 0x78)
    img[0x11A:0x11C] = struct.pack(">H", 0xF495)
    return bytes(img)


def test_adjacent_table_stops_at_second_loader():
    buf = build_two_adjacent()
    blocks, end = walk(buf, 0x100)
    data = [b for b in blocks if not b["placeholder"]]
    assert len(data) == 1 and data[0]["flash"] - FLASH_BASE == 0x100
    assert end == 0x10E


if __name__ == "__main__":
    fns = [v for k, v in sorted(globals().items())
           if k.startswith("test_")]
    for fn in fns:
        fn()
        print(f"PASS {fn.__name__}")
    print(f"{len(fns)} tests passed")
