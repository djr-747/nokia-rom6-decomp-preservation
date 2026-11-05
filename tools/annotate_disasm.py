# Emit annotated C54x disassembly: objdump output interleaved with
# roms/rom6/symbols.yaml entries. Usage:
#   python3 tools/annotate_disasm.py --image <program.be16> --objdump <tic54x-objdump>
#       --symbols roms/rom6/symbols.yaml --base 0xB4F8 --words 64
# BE words are byte-swapped to LE for the LE-hardwired BFD, matching
# the decomp workflow. Output goes to stdout: `NAME:` labels plus
# `;` notes ahead of the owning instruction, nothing else added, so
# the listing stays recombination-clean (addresses verbatim).
import argparse
import struct
import subprocess
import sys
import tempfile

try:
    import yaml
except ImportError:
    sys.exit("need pyyaml")


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
    for line in out.stdout.splitlines():
        # objdump section-relative rows look like `  ab:\t1234 \tmnem...`
        # with the address in file-offset hex.
        stripped = line.strip()
        head = stripped.split(":")[0] if ":" in stripped else ""
        try:
            off = int(head, 16)
        except ValueError:
            print(line)
            continue
        addr = base + off
        if addr in names and "\t" in line:
            print(f"{names[addr]}:  ; 0x{addr:04X}")
            print(line)
            continue
        if "\t" in line:
            # bare operand word row: tag it when it names a data cell
            cell = line.split("\t")[-1].strip()
            try:
                if int(cell, 16) in data_names:
                    print(f"{line}  ; *({cell}) = "
                          f"{data_names[int(cell, 16)]}")
                    continue
            except ValueError:
                pass
        print(line)


main()
