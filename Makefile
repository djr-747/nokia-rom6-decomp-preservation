# Per-target defaults; override on the command line, e.g. ROM=rom4.
ROM ?= rom6
BUILD := build/$(ROM)
OBJDUMP ?= $(shell ls ../nokia-dct3-emu/build/tic54x-objdump 2>/dev/null)

.PHONY: verify disasm disasm-rom6 disasm-rom4 fingerprint test help

help:
	@echo "targets: verify | test | disasm [ROM=rom6|rom4|rom3|rom5] | fingerprint FLS=path/to/phone.fls"

test:
	python3 tests/test_table_walk.py
	python3 tests/test_verdict.py

verify:
	python3 tools/verify_images.py --rom $(ROM)

fingerprint:
	python3 tools/fingerprint.py --fls "$(FLS)"

disasm: verify
	python3 tools/disasm_c54x.py --rom $(ROM) --objdump "$(OBJDUMP)"

disasm-rom6:
	$(MAKE) disasm ROM=rom6

disasm-rom4:
	$(MAKE) disasm ROM=rom4
