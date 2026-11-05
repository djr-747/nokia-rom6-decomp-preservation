# Emit annotated C54x disassembly: objdump output interleaved with
# roms/rom6/symbols.yaml entries. Usage:
#   python3 tools/annotate_disasm.py --image <program.be16> --objdump <tic54x-objdump>
#       --symbols roms/rom6/symbols.yaml --base 0xB4F8 --words 64
# BE words are byte-swapped to LE for the LE-hardwired BFD, matching
# the decomp workflow. Output goes to stdout. Labels: every symbol
# address gets `NAME:  ; 0xADDR`; every in-window branch/call target
# without a symbol gets `L_ADDR:`. Branch lines carry `; -> TARGET`
# and data operands `*(0x..)` carry `; = NAME`. Addresses stay
# verbatim, so listings stay recombination-clean.
import argparse
import re
import struct
import subprocess
import sys
import tempfile

try:
    import yaml
except ImportError:
    sys.exit("need pyyaml")

ROW = re.compile(r"^\s*([0-9a-f]+):\t([0-9a-f]+)\s*(.*)$")
BRANCH = {"b", "bc", "cc", "call", "calld", "fb", "bd", "banz",
          "rptb", "trap"}
DATAREF = re.compile(r"\*\(0x([0-9a-f]+)\)")
HEXOP = re.compile(r"0x([0-9a-f]+)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--image", required=True)
    ap.add_argument("--objdump", required=True)
    ap.add_argument("--symbols", required=True)
    ap.add_argument("--base", required=True)
    ap.add_argument("--words", type=int, required=True)
    args = ap.parse_args()

    base = int(args.base, 0)
    raw = open(args.image, "rb").read()
    img = struct.unpack(f">{len(raw) // 2}H", raw)
    window = img[base:base + args.words]
    end = base + len(window)

    d = yaml.safe_load(open(args.symbols))
    names = {}
    data_names = {}
    for key, space in d["spaces"].items():
        for s in space["symbols"]:
            names[s["address"]] = s["name"]
            if key == "data_word":
                data_names[s["address"]] = s["name"]

    with tempfile.NamedTemporaryFile(suffix=".le", delete=False) as f:
        f.write(struct.pack(f"<{len(window)}H", *window))
        tmp = f.name
    out = subprocess.run([args.objdump, "-b", "binary", "-m", "tic54x",
                          "-D", tmp], capture_output=True, text=True)

    rows = []  # (addr, word, disasm, rawline)
    for line in out.stdout.splitlines():
        m = ROW.match(line)
        if not m:
            rows.append((None, None, None, line))
            continue
        off = int(m.group(1), 16)
        rows.append((base + off, m.group(2), m.group(3), line))

    # pass 1: collect branch/call targets
    targets = {}  # target addr -> set of source addrs
    for addr, word, dis, _ in rows:
        if addr is None or not dis:
            continue
        parts = dis.split()
        if not parts or parts[0] not in BRANCH:
            continue
        hm = HEXOP.search(dis)
        if hm:
            targets.setdefault(int(hm.group(1), 16), set()).add(addr)

    def label(t):
        return names.get(t, f"L_{t:04X}")

    # pass 2: emit
    for addr, word, dis, rawline in rows:
        if addr is None:
            print(rawline)
            continue
        if addr in targets and base <= addr < end:
            print(f"{label(addr)}:  ; 0x{addr:04X}")
        elif addr in names:
            print(f"{names[addr]}:  ; 0x{addr:04X}")
        line = rawline
        if dis:
            parts = dis.split()
            tag = None
            if parts and parts[0] in BRANCH:
                hm = HEXOP.search(dis)
                if hm:
                    t = int(hm.group(1), 16)
                    tag = f"-> {label(t)}"
            else:
                dm = DATAREF.search(dis)
                if dm:
                    cell = int(dm.group(1), 16)
                    if cell in data_names:
                        tag = f"= {data_names[cell]}"
            if tag:
                line = f"{line}  ; {tag}"
        print(line)


main()
