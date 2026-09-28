#!/usr/bin/env bash
set -euo pipefail

# Root of project (directory containing this script)
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR"

# Ensure binaries exist
if [[ ! -x "./mini" || ! -x "./asm" || ! -x "./machine" ]]; then
  echo "error: missing binaries. Please run 'make' first." >&2
  exit 1
fi

TEST_DIR="$ROOT_DIR/testcase"
RESULT_DIR="$ROOT_DIR/results"
mkdir -p "$RESULT_DIR"

# Input overrides per test base name
# Define associative array only in bash 4+
declare -A INPUTS
INPUTS["loop"]=$'1\n2\n3\n'

# Iterate all .m files
shopt -s nullglob
for mfile in "$TEST_DIR"/*.m; do
  base="$(basename "$mfile" .m)"
  sfile="$TEST_DIR/$base.s"
  ofile="$TEST_DIR/$base.o"
  xfile="$TEST_DIR/$base.x"
  outfile="$RESULT_DIR/$base.out.txt"

  echo "[RUN] $base"

  # Compile to TAC/ASM
  ./mini "$mfile"
  ./asm "$sfile"

  # Run machine with optional input
  if [[ -n "${INPUTS[$base]:-}" ]]; then
    printf "%s" "${INPUTS[$base]}" | ./machine "$ofile" > "$outfile" 2>&1
  else
    ./machine "$ofile" > "$outfile" 2>&1
  fi

  echo "[DONE] $base -> $outfile"
done

# Summary
echo "\nAll tests finished. Outputs are in: $RESULT_DIR"