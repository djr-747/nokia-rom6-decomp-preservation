#!/usr/bin/env bash
# Build the TI C54x assembler + objcopy from upstream binutils and install
# them as tic54x-as / tic54x-objcopy under $PREFIX/bin (default $HOME/.local/bin).
# Same source recipe the emulator uses for tic54x-objdump (tools/dsp/disasm.sh):
#   binutils-2.42 --target=tic54x-coff, gas + binutils only.
set -euo pipefail
PREFIX="${PREFIX:-$HOME/.local/bin}"
VER="${VER:-2.42}"
WORK="${WORK:-/tmp/bu-recomp}"
mkdir -p "$WORK" "$PREFIX"
cd "$WORK"
if [ ! -f "binutils-$VER.tar.xz" ]; then
  curl -sL "https://ftp.gnu.org/gnu/binutils/binutils-$VER.tar.xz" -o "binutils-$VER.tar.xz"
fi
rm -rf "src-binutils-$VER"
mkdir "src-binutils-$VER"
tar xJf "binutils-$VER.tar.xz" -C "src-binutils-$VER"
cd "src-binutils-$VER/binutils-$VER"
mkdir -p build && cd build
../configure --target=tic54x-coff --program-prefix=tic54x- \
  --disable-nls --disable-werror --disable-gdb --disable-sim >/dev/null
make -j"$(nproc)" MAKEINFO=true all-gas all-binutils >/dev/null
cp gas/as-new "$PREFIX/tic54x-as"
cp binutils/objcopy "$PREFIX/tic54x-objcopy"
echo "installed: $PREFIX/tic54x-as $PREFIX/tic54x-objcopy"
"$PREFIX/tic54x-as" --version | head -1
