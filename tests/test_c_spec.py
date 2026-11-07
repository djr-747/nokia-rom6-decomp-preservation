#!/usr/bin/env python3
"""C-spec gate: tools/check_c.py must pass (or cleanly SKIP without images)."""
import subprocess
import sys


def main():
    r = subprocess.run([sys.executable, "tools/check_c.py"],
                       capture_output=True, text=True, cwd=".")
    sys.stdout.write(r.stdout)
    assert r.returncode == 0, "check_c.py failed"
    print("test_c_spec: OK")


if __name__ == "__main__":
    main()
